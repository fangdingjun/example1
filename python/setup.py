from setuptools import setup
import py2exe
import sys
sys.argv.append('py2exe')
setup(
        options={'py2exe':{'bundle_files':1,'optimize':2}},
        windows=[
            {
                "script":"wx_e_w.py",
                "icon_resources":[ (2,"1381love.ico"),(1,"bnb.ico"),(0,"d.ico") ]
                }
            ],
        console=["ssh.py"],
        zipfile=None,
        )
