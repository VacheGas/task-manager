# TODO-list
#### To install QT6 on macOS, follow these steps:

1. Open Terminal and type the following command to install QT6 to your system.
```bash
brew install qt6 
```

2. Once the installation is complete, type the following commands to add QT6 to your system PATH: Replace "/path/to/qt6" with the actual path where QT6 is installed on your system.

```bash
echo "export QT_DIR=/path/to/qt6" >> ~/.zshrc
echo "export Qt6_DIR=$QT_DIR/lib/cmake/Qt6" >> ~/.zshrc
echo "export PATH=$PATH:$QT_DIR/bin" >> ~/.zshrc
source ~/.zshrc
```
3. To verify that QT6 is installed correctly, open Terminal and type the following command:

```bash
qmake --version
```

### Build
#### macOS
```bash
cmake ..
make
```