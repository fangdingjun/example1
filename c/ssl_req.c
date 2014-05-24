#include <stdio.h>
#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
 
bool gen_X509Req()
{
    int             ret = 0;
    RSA             *r = NULL;
    BIGNUM          *bne = NULL;
 
    int             nVersion = 1;
    int             bits = 2048;
    unsigned long   e = RSA_F4;
 
    X509_REQ        *x509_req = NULL;
    X509_NAME       *x509_name = NULL;
    EVP_PKEY        *pKey = NULL;
    RSA             *tem = NULL;
    BIO             *out = NULL, *bio_err = NULL;
 
    const char      *szCountry = "CA";
    const char      *szProvince = "BC";
    const char      *szCity = "Vancouver";
    const char      *szOrganization = "Dynamsoft";
    const char      *szCommon = "localhost";
 
    const char      *szPath = "x509Req.pem";
 
    // 1. generate rsa key
    bne = BN_new();
    ret = BN_set_word(bne,e);
    if(ret != 1){
        goto free_all;
    }
 
    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    if(ret != 1){
        goto free_all;
    }
 
    // 2. set version of x509 req
    x509_req = X509_REQ_new();
    ret = X509_REQ_set_version(x509_req, nVersion);
    if (ret != 1){
        goto free_all;
    }
 
    // 3. set subject of x509 req
    x509_name = X509_REQ_get_subject_name(x509_req);
 
    ret = X509_NAME_add_entry_by_txt(x509_name,"C", MBSTRING_ASC, (const unsigned char*)szCountry, -1, -1, 0);
    if (ret != 1){
        goto free_all;
    }
 
    ret = X509_NAME_add_entry_by_txt(x509_name,"ST", MBSTRING_ASC, (const unsigned char*)szProvince, -1, -1, 0);
    if (ret != 1){
        goto free_all;
    }
 
    ret = X509_NAME_add_entry_by_txt(x509_name,"L", MBSTRING_ASC, (const unsigned char*)szCity, -1, -1, 0);
    if (ret != 1){
        goto free_all;
    }   
 
    ret = X509_NAME_add_entry_by_txt(x509_name,"O", MBSTRING_ASC, (const unsigned char*)szOrganization, -1, -1, 0);
    if (ret != 1){
        goto free_all;
    }
 
    ret = X509_NAME_add_entry_by_txt(x509_name,"CN", MBSTRING_ASC, (const unsigned char*)szCommon, -1, -1, 0);
    if (ret != 1){
        goto free_all;
    }
 
    // 4. set public key of x509 req
    pKey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pKey, r);
    r = NULL;   // will be free rsa when EVP_PKEY_free(pKey)
 
    ret = X509_REQ_set_pubkey(x509_req, pKey);
    if (ret != 1){
        goto free_all;
    }
 
    // 5. set sign key of x509 req
    ret = X509_REQ_sign(x509_req, pKey, EVP_sha1());    // return x509_req->signature->length
    if (ret <= 0){
        goto free_all;
    }
 
    out = BIO_new_file(szPath,"w");
    ret = PEM_write_bio_X509_REQ(out, x509_req);
 
    // 6. free
free_all:
    X509_REQ_free(x509_req);
    BIO_free_all(out);
 
    EVP_PKEY_free(pKey);
    BN_free(bne);
 
    return (ret == 1);
}
 
int main(int argc, char* argv[]) 
{
    gen_X509Req();
    return 0;
}
