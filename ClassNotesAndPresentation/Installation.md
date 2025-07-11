
---

# Software Requirements

---
## Installing NodeJS
#### In Windows 
- Open up the NodeJS Download and Download the .msi file and Simply install you can directly download the file By clicking [here](https://nodejs.org/dist/v22.17.0/node-v22.17.0-x64.msi)
### In Ubuntu 

- Open Terminal ( Press `Ctrl + Alt + T` )
- Type in these commands 
```sh

curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash

\. "$HOME/.nvm/nvm.sh"

nvm install 22

node -v # Should print "v22.17.0".
nvm current # Should print "v22.17.0".
# Verify npm version:
npm -v # Should print "10.9.2".
```

## Install Visual Studio Code

### In Windows
- Download Visual studio code installation file from [website](https://code.visualstudio.com/download) and install it.
- For Ubuntu type in the command  `snap install code --classic`

## Installing platformio
### Inside Visual Studio code
- Go to extensions and install the platfomio Extension
#### Installing In Core :
- Make sure python is installed in both Ubuntu and Windows and added as path variable
```sh
python
# Should Output something like 
#Python 3.13.5 (main, Jun 21 2025, 09:35:00) [GCC 15.1.1 20250425] on linux
#Type "help", "copyright", "credits" or "license" for more information.

pip
#should output
#pip <command> [options]

#Commands:
#  install                     Install packages.
#  lock                        Generate a lock file.
#  download                    Download packages.
#  uninstall                   Uninstall packages.
#  freeze                      Output installed packages in requirements #format.
#  inspect                     Inspect the python environment.
#  list                        List installed packages.
#  show                        Show information about installed packages.

```

### If success type In :
`pip install -U platformio`

### Driver Installation 

#### Windows Users Also install the CH340 Uart Driver also in theri Sytem

[Website Link](https://sparks.gogo.co.nz/assets/_site_/downloads/CH34x_Install_Windows_v3_4.zip)
