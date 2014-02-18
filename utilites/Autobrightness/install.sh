echo "Hello $USER. This is an \"install-script\" to install....."
echo "AutoBrightness"

echo "Installing....."

sleep 5

sudo apt-get install libopencv-highgui2.4
sudo apt-get install libopencv-imgproc2.4
sudo apt-get install libopencv-objdetect2.4
sudo apt-get install xdotool

sudo mkdir -v /opt/AutoBrightness
sudo cp -v ./* /opt/AutoBrightness/

echo "alias autobrightness=\"bash /opt/AutoBrightness/run.sh\" " >> ~/.bashrc
echo "Install complete.. type 'autobrightness' to run the plugin"
source ~/.bashrc
