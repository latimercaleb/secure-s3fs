# secure-s3fs
Secured implementation of s3fs file system with rc4 encryption 
CSC 4420: Operating Systems Design, Course Final Project

This project is to create a stackable file system on Linux using Amazon S3 as the back end storage that will accomplish the following:
- On Mount, a bucket from S3 is part of the file directory on your Linux machine
- Any updates will be reflected on both ends
- All files are encrypted automatically via upload using openssl RC4 implementation 

## Setup: 

#### First setup an AWS account with amazon webservices and create a name for a bucket do this by:

- In your web browser navigate to aws.amazon.com
- Click storage then s3
- Click get started with Amazon s3 
- If you have an account log in or make a new account
- Follow the options and make a bucket 

#### Second download and install s3fs
- Install required dependancies on Ubuntu via terminal by using the following command:
```
sudo apt-get install automake autotools-dev g++ git libcurl4-gnutls-dev libfuse-dev libssl-dev libxml2-dev make pkg-config
```
- Navigate to your home directory and create a script called automount let it contain the following:
```
#!/bin/bash
#shebang above for bourne shell execution

#unmount folder if currently mounted, used for remounting
fusermount -u ./MyMount

# Add the path thing to point to the right path
PATH=$PATH:/home/kaz/Desktop/4420Project/s3fs-fuse/src

#Run the command to check which directory for s3fs
which s3fs

#Add the mount command to to the mount
# add -d -d for the debug mode in order to view data
s3fs babylon ~/MyMount -o passwd_file=~/.passwd-s3fs -o umask=0000

#bash script by Caleb Latimer ej1297
```

- Make a new directory called MyMount in the same directory as the script and exchange "babylon" with the name of your own bucket. 
- Navigate back to directory you'd like to install s3fs into
- Install my s3fs by running the following: 
```
git clone https://github.com/latimercaleb/secure-s3fs
cd secure-s3fs
./autogen.sh
./configure
make
```

## Configure 

#### Modify the above script to match your installation:
- fusermount -u ./myMountpathandlocation
- PATH=$PATH:/home/whereveryouinstalleds3fs
- which s3fs
- s3fs thebucketnameyouhave ~/pathtoyourmountpoint -o passwd_fle=~/.passwd-s3fs -o umask=0000

#### Making the passwd file: 

The password file must have your s3 authentication credentials find those credentials by doing the following: 

- Navigate to your username in the s3 browser on aws.amazon.com
- Click security credentials
- Click access Keys and generate a new one

Once you have the file make store your information in the passwd file in the following format:
```
MYIDENTITY:MYCREDENTIAL
```

## Notes: 
Encryption key: The encryption key is embedded in two locations that will need to be changed in order to match your security preferrence. The encryption key must be on one line and can have alphanumerics or digits

First, open the pass.txt file located in s3fs/src and enter the text you'd like to use as your key.
Second, open fdcache.cpp on line 89 and set` code="whateveryouenteredinstep1";` (NOTE: this is not mandatory but is a fail-safe in the case of performance issues).

If the encryption key is changed you must navigate back to secure-s3fs/ and run ``make``

## Other notes:

- Not fully tested with multiple file extensions functionality guaranteed for text, gif, png and jpg files 
- Tested on up to 8MB files larger files may result in undefined behavior
- Once the script is put together it must be run with ./myscriptname
- Use df to see if s3fs is mounted, use man df for more information

