#include <stdio.h>
#include <iostream>
 
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/objects.h>
#include <openssl/ocsp.h>
 
// load ca
bool loadCA(const char *f, X509 ** px509)
{
    bool ret;
    BIO *in = NULL;
 
    in = BIO_new_file(f,"r");
 
    ret = (PEM_read_bio_X509(in, px509, NULL, NULL) != NULL);
 
    BIO_free(in);
    return ret;
}
 
// load ca private key
bool loadCAPrivateKey(const char *f, EVP_PKEY **ppkey)
{
    bool ret;
    BIO *in = NULL;
    RSA *r = NULL;
    EVP_PKEY *pkey = NULL;
 
    in = BIO_new_file(f,"r");
    ret = (PEM_read_bio_RSAPrivateKey(in, &r, NULL, NULL) != NULL);
    if(!ret)
        goto free_;
 
    pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, r);
    *ppkey = pkey;
    r = NULL;
 
free_:
    BIO_free(in);
    return ret;
}
 
// load X509 Req
bool loadX509Req(const char *f, X509_REQ **ppReq)
{
    bool ret;
    BIO *in = NULL;
 
    in = BIO_new_file(f,"r");
    ret = (PEM_read_bio_X509_REQ(in, ppReq, NULL, NULL) != NULL);
 
free_:
    BIO_free(in);
    return ret;
}
 
// sign cert
int do_X509_sign(X509 *cert, EVP_PKEY *pkey, const EVP_MD *md)
{
    int rv;
    EVP_MD_CTX mctx;
    EVP_PKEY_CTX *pkctx = NULL;
 
    EVP_MD_CTX_init(&mctx);
    rv = EVP_DigestSignInit(&mctx, &pkctx, md, NULL, pkey);
 
    if (rv > 0)
        rv = X509_sign_ctx(cert, &mctx);
    EVP_MD_CTX_cleanup(&mctx);
    return rv > 0 ? 1 : 0;
}
 
bool sign_X509_withCA()
{
    int             ret = 0;
 
    const char      *caFile = "cacert.pem";
    const char      *caPrivateKeyFile = "cakey.pem";
    const char      *x509ReqFile = "x509Req.pem";
 
    const char      *szUserCert = "cert.pem";
 
    int serial = 1;
    long days = 3650 * 24 * 3600; // 10 years
    char *md = NULL;
 
    X509 * ca = NULL;
    X509_REQ * req = NULL;
    EVP_PKEY *pkey = NULL, *pktmp = NULL;
 
    X509_NAME *subject = NULL, *tmpname = NULL;
    X509 * cert = NULL;
    BIO *out = NULL;
 
    if(!loadCA(caFile, &ca))
        goto free_all;
 
    if(!loadCAPrivateKey(caPrivateKeyFile, &pkey))
        goto free_all;
 
    if(!loadX509Req(x509ReqFile, &req))
        goto free_all;
 
    cert = X509_new();
    // set version to X509 v3 certificate
    if (!X509_set_version(cert,2)) 
        goto free_all;
 
    // set serial
    ASN1_INTEGER_set(X509_get_serialNumber(cert), serial);
 
    // set issuer name frome ca
    if (!X509_set_issuer_name(cert, X509_get_subject_name(ca)))
        goto free_all;
 
    // set time
    X509_gmtime_adj(X509_get_notBefore(cert), 0);
    X509_gmtime_adj(X509_get_notAfter(cert), days);
 
    // set subject from req
    tmpname = X509_REQ_get_subject_name(req);
    subject = X509_NAME_dup(tmpname);
    if (!X509_set_subject_name(cert, subject)) 
        goto free_all;
 
    // set pubkey from req
    pktmp = X509_REQ_get_pubkey(req);
    ret = X509_set_pubkey(cert, pktmp);
    EVP_PKEY_free(pktmp);
    if (!ret) goto free_all;
 
    // sign cert
    if (!do_X509_sign(cert, pkey, EVP_sha1()))
        goto free_all;
 
    out = BIO_new_file(szUserCert,"w");
    ret = PEM_write_bio_X509(out, cert);
 
free_all:
 
    X509_free(cert);
    BIO_free_all(out);
 
    X509_REQ_free(req);
    X509_free(ca);
    EVP_PKEY_free(pkey);
 
    return (ret == 1);
}
 
int main(int argc, char* argv[]) 
{
    sign_X509_withCA();
    return 0;
}
