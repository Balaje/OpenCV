echo "What is your Operating System?"
echo "(1)Ubuntu"
echo "(2)Arch Linux"
echo "(3)RPM Based"
echo "Enter Your Choice (1/2/3):"
read choice;

if [ $choice -eq 1 ]
then
	bash ubuntu_install.sh
	sudo apt-get install xdotool
fi

if [ $choice -eq 2 ]
then 
	sudo pacman -S opencv
	sudo pacman -S xdotool
fi

if [ $choice -eq 3 ]
then 
	yum install sudo
	yum install opencv
	yum install xdotool
fi

mkdir images

name=sycon.cpp
cd src
echo "Compiling the source code \"$name\" "
g++ -ggdb `pkg-config --cflags opencv` -o `basename $name .cpp` $name `pkg-config --libs opencv`;
cd ..
ls src

cp -v src/sycon sycon
sudo mkdir /opt/SyCon
sudo mkdir /opt/SyCon/haar
sudo mkdir /opt/SyCon/images
sudo mkdir /opt/SyCon/src
sudo cp -v haar/* /opt/SyCon/haar/
sudo cp -v images/* /opt/SyCon/images/
sudo cp -v src/* /opt/SyCon/src/
sudo cp -v install.sh /opt/SyCon/ 
sudo cp -v sycon /opt/SyCon/sycon
cp -v .exec.sh ~
echo "alias sycon='bash ~/.exec.sh'" >> ~/.bashrc
source ~/.bashrc
echo ""
echo ""
echo "Software Installed... Run 'sycon' to try it"
