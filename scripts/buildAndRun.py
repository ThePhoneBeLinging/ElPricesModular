import os
import subprocess

if not os.path.exists("build"):
        os.makedirs("build")
os.environ['MESA_GL_VERSION_OVERRIDE'] = '4.5'
os.environ['DISPLAY'] = ':0'
subprocess.run(["git","pull"], check = True)
subprocess.run(['python3',"scripts/loadExternals.py"], check=True)
subprocess.run(['python3',"scripts/updateExternals.py"], check=True)
subprocess.run(['cmake',".."], cwd = "build", check=True)
subprocess.run(['make'], cwd = "build", check=True)
subprocess.run(['./ElPricesModular'], cwd = "build/src", check=True)