import os
import subprocess

if not os.path.exists("build"):
        os.makedirs("build")


os.system("cd build")
os.system("cmake ..")
os.system("make")
os.system("cd src")
os.system("./ElPricesModular")