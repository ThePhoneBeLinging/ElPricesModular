# ElPricesModular

Dependencies:

``` bash
sudo apt install libssl-dev libsqlite3-dev libfmt-dev xorg-dev gpiod libgpiod-dev libasio-dev
```

GLX: Failed to create context: GLXBadFBConfig
Run the following:
``` bash 
export MESA_GL_VERSION_OVERRIDE=4.5
```

To launch the application use:
``` bash 
python3 scripts/buildAndRun.py
```

If you attempt to use a port less than 1024, you will need to run the program as a root user.
To do this, run the build command listed above (python3 scripts/buildAndRun.py). It will fail, you can then write:
``` bash 
cd build/src
```

Followed by:
``` bash 
sudo ./ElPricesModular
```

Security experts might say that it would be better to run on a port above 1024, and simply make your device redirect.
(And they are likely correct, but the application should only need root access the first time, the python script for building and running should then work)