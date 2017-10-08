# KIFT
[Installing pocketshpinx](http://www.moreiscode.com/getting-started-with-cmu-sphinx-on-mac-os-x/).
If your dependencies don't install, consult The Oracle.
Use commands below to compile the necessary binaries.
```
gcc -o client client.c -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`

gcc -o server server.c -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`
```
Launch the server.
```
./server
```
Under - Mac > System Preferences > Network - you can find the IP of your local machine.
Use this IP as a command-line argument when you launch the client, otherwise it won't connect.
```
./client <local.ip.address>
```
Once connected, the program currently just records whatever is happening. It might record infinitely. When you kill the process it will output to a valid .wav file. I'm working on sending that file in tact.
