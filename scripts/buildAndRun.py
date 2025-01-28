import os
import subprocess

if not os.path.exists("build"):
        os.makedirs("build")
subprocess.run(["git","pull"])
subprocess.run(['python3',"scripts/loadExternalsSSH.py"], check=True)
subprocess.run(['cmake',".."], cwd = "build", check=True)
subprocess.run(['make'], cwd = "build", check=True)
subprocess.run(['./ElPricesModular'], cwd = "build/src", check=True)