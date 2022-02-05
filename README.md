# <p align="center"> Operative Systems H2 </p>

<p align="center"> Upgrading the xv6-fs file system </p>

The goal of the homework is to modify the xv6 system to support the following file system functionalities:

● Create, read, write, edit and delete large files using the double indirect cursor in the inode structure.

● Encrypt the contents of certain files on disk.

In addition to these file system functionalities, the following system calls and user programs need to be implemented:

● System calls:

  ○ int setkey (int key);

  ○ int setecho (int echo);

  ○ int encr (int fd);

  ○ int decr (int fd);

● User programs:

  ○ setkey

  ○ encr

  ○ decr

  ○ blockwriter


## Double indirect node

>Change the inode (both inode and dinode) structure to support double indirect pointer to blocks. After the change, one file should be able to consist of 11 + 128 + 128 \* 128 blocks. Do a thorough research of the file system and make sure it works in all cases. 
It is not necessary to change the mkfs tool.

## Encryption and decryption
>The Caesar code is used for encryption purposes. This code requires setting one int number as the key for encryption and decryption, and should work for all characters in the ASCII table. The setting of this key is done using a system call setkey, and the key is global at the level of the entire operating system. 
The key is always a positive number or zero. Any user program can make this call to change the global key.
Once the key is set, a file already on disk can be encrypted or decrypted using the encr and decr system calls. 
Both system calls expect the file to be already open for reading and writing.
In addition, it is necessary to change the behavior of read / write system calls so that they automatically decrypt / encrypt when reading / writing. The files will have the encryption information recorded in the major attribute in the inode structure: 0 means that the file is not encrypted, and 1 means that it is. These operations use a globally set decryption / encryption key. 
If the wrong key is used when reading the file, it is expected that meaningless text will be obtained as a result of reading.

## System calls
System calls must not print on the screen. All printing, whether the system call was successful or not, must be performed by user programs.

int setecho (int do\_echo);

The system call disables or enables echo functionality on the console. If the passed parameter is 1, the system is operating normally. 
If the passed parameter is 0, all characters except &#39;\ n&#39; are printed on the console as &#39;\*&#39;. 
The system call returns -1 if an error occurred while making a system call, and 0 otherwise.

int setkey (int key);

The passed parameter is the key that will be used for encryption and decryption. 
The system call returns -1 if an error occurred while making a system call, and 0 otherwise.

int encr (int fd);

The system call encrypts the file using the currently set global encryption key. 
The forwarded parameter is the file descriptor of the file to be encrypted, and the file is expected to be open for reading and writing. T\_DEV files cannot be encrypted. 
The return value can be one of:

 ● -1: key not set.
 ● -2: The file is of T\_DEV type.
 ● -3: The file is already encrypted.
 ● 0: The system call ended successfully.

int decr (int fd);

The system call decrypts the file using the currently set global decryption key. The forwarded parameter is the file descriptor of the file to be decrypted, and the file is expected to be open for reading and writing.
Files of type T\_DEV cannot be decrypted. The return value can be one of:

 ● -1: key not set.
 ● -2: The file is of T\_DEV type.
 ● -3: The file is not encrypted.
 ● 0: The system call ended successfully.

## User programs
 If an error occurs while making a system call, the user program must print a meaningful error message, informing the user that this has happened.
The setkey program will allow you to set the encryption and decryption keys. The encr and decr programs will allow you to encrypt and decrypt existing files on disk. Finally, blockwriter will allow you to create a file that takes up arbitrarily many blocks and contains simple and predictable text.

 blockwriter

 blockwriter creates a new file in the current directory that is the specified size in the blocks with the specified name. The default values ​​are 150 blocks and the file name is long.txt. The user of this program can change these values ​​with piece line arguments.
 
Options:
 ● --help (-h) displays the help menu.
 ● --output-file (-o) FILENAME sets the name for the newly created FILENAME file.
 ● --blocks (-b) BLOCKS sets the number of blocks to print to BLOCKS.

 setkey

 setkey sets the system key to a value using a system call setkey, which is entered via command line parameters or via STDIN.

Options:
 ● --help (-h) displays the help menu.
 ● --sec
 ● --ret (-s) takes the key from STDIN and hides the key using the setecho system call.
  
 encr 
 
 encr encrypts one or more files by calling the encr system call. If the encryption file name is omitted, print the help menu.

Options:
● --help (-h) displays the help menu.
● --encrypt-all encrypts all non-encrypted files in the current directory.

decr

decr decrypts one or more files by calling the decr system call. If the decryption file name is omitted, print the help menu.

Options:
● --help (-h) displays the help menu.
● --decrypt-all decrypts all encrypted files in the current directory.
