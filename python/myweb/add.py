from django.http import HttpResponse
text="""
<form method="post" action="/add/">
<input type="text" name="a" value="%d"> +
<input type="text" name="b" value="%d"> =
<input type="text" value="%d">
<input type="submit" value="ok">
</form>
"""
def index(req):
    #res=HttpResponse("hello")
    #return res
    if req.POST.has_key("a"):
        try:
            a=int(req.POST["a"])
        except:
            a=0
        try:
            b=int(req.POST["b"])
        except:
            b=0
    else:
        a=0
        b=0
    return HttpResponse(text % (a,b,a+b))
