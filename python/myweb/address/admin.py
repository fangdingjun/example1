from myweb.address.models import Address
from django.contrib import admin
admin.site.register(Address)

class DocumentAdmin(admin.ModelAdmin):
    pass

class CommentAdmin(admin.ModelAdmin):
    pass

#admin.site.register(Address.Document, DocumentAdmin)
#admin.site.register(Address.Comment, CommentAdmin)
#admin.site.register(Address)
