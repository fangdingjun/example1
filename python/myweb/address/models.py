# -*- coding: utf-8 -*
from django.db import models

# Create your models here.
class Address(models.Model):
    name = models.CharField('姓名', max_length=6, unique=True)
    gender = models.CharField('性别', choices=(('M', '男'), ('F', '女')),
        max_length=1, )
    telphone = models.CharField('电话', max_length=20)
    mobile = models.CharField('手机', max_length=11)
    """ 
    def __repr__(self):
        return self.name
    def __str__(self):
        return self.name
        """
    def __unicode__(self):
        return self.name

class Admin:pass
