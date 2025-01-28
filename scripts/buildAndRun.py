import os
import subprocess

if not os.path.exists("build"):
        os.makedirs("build")
subprocess.run(['cmake',".."], cwd = "build", check=True)
subprocess.run(['make'], cwd = "build", check=True)
subprocess.run(['./ElPricesModular'], cwd = "build/src", check=True)