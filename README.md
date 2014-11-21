Readme
======

This SVN has some updates to the Einstein emulator.  Nothing that
will improve performance sadly.  Some high level changes:

 - Updated the code to for iOS8, using storyboards.
 - Support for new resolutions (iPhone 6, 6+)
 - Fix for screen rotation

Jake
====

If you're a Newton old timer, you might remember "The Newton Underground"
website.  Will Nelson started the site and in time is let accepted me
as a sort of assistant moderator.  You might also recognize a few of my 
Newton apps, including NewtonIM, a Jabber client, and NUDrop a  Newton 
Underground themed backdrop.

Original Einstein Readme
========

This version of Einstein features emulation for an NE2000
networking PCMCIA card. There are still a lot of missing 
features and bugs, but for testing, you can do this:

- compile and run this version of Einstein
- in preferences, set the Network Driver to "User Mode"
- launch the emulation 
- install all ethernet related packages from NIE 2.0
- install "./Drivers/NE2000Driver/NE2K.pkg"
- install "Courier" and its libraries
- "insert" the NE2000 card by choosing "Platform->Insert NE2000 Card"
  from the Einstein Menu 
- the "PCMCIA Ethernet" dialog should appear, close it
- in "Extras", open "Internet Setup"
- click "New -> Generic Setup"
- configure manually and set the local IP to the IP of the host
- set the Mask, Gateway, and DNS (no DHCP yet!)
- close the dialog
- run Courier
- click the single arrow [->o] 
- enter "borg.org" as a destination (some random minimal web site)
- in the connection dialog, choose your internet setup, then choose
  "PCMCIA Ethernet" as your Card, and tap on "Connect"
- after 10 to 20 seconds, Mr. Borg will give you the disappointing
  information that he is no fan of Captain Kirk.

Please let me know if your connection works. I'll be happy to hear 
from you. Email einstein at matthiasm dot com.

Matthias

