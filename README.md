# FYS-Assignment

## Using the Program
----
#### Running the Program
This will vary a bit depending on the platform you're using. To simplify the process, the only file that will need to be clicked on will be called `runMe.something`. The **something** won't matter, all of the different versions will do the same thing.
#### Loading Files into the App
The program accepts any of the following: `csv`, `xls`, or `xlsx`.
To load them in, click on the **Browse** button in the application. It will be easier if all of the files are in the same location, as well as in the same folder as the application.
##### Loading in the Students' selections
The first file that will need to be loaded in is what the students' selections are. This should look like the following:

| FirstName | LastName   | DRAKE ID  | FYSSelectedCourses | CRNSelectedCourses |
| --------- | ---------- | --------- | ------------------ | ------------------ |
| Joe       | Schmo      | 000000123 | FYS 1, FYS 6, FYS 37, FYS 42, FYS 48 | CRN 2931, CRN 6456, CRN 6976, CRN 6979, CRN 6983 |

Just click the **Browse** button, find the `csv`, `xls`, or `xlsx` file with the selections, and hit open. The **Student File** text should change to the path where the file was located.

##### Loading in the Courses file
The process is the same as the above, just click the **Browse** button and select the file. The course file should be formatted like so:

| FYS   | CRN      | Slots Available |
| ----- | -------- | --------------- |
| FYS 1 | CRN 2931 | 5 |

#### Creating Output
This is the easiest part (besides clicking the **Assign** button). Just click the button and name the file whatever you'd like to name it. The only thing that needs to happen is that it needs to be a `csv` file. So if one was going to name the file `FYS Session 1 20XX`, what would need to be typed in is `FYS Session 1 20XX.csv`. 

#### The Randomize Button
One problem identified the first year this was tested was that the lower numbered FYSs were getting filled quicker. In an attempt to unskew this, the randomize button was added. This simply shuffles the order of the courses that are fed in via the file above. If the **Randomize** button is unchecked, the courses will **not** be shuffled.

#### Multiple Runs
If you want to run the data through multiple times, either with the randomize button off and then on or on the whole time, the save file will need to be changed in order to see the new results. So each time the program is run, one will have to click browse and create a new save file before running it again.

## Installing on a Mac
----
Macs come installed with Python 2.7.X, so the fys-assignment.py will need to have the `import` statements for Python 3 commented out, and the `import` statements for Python 2 uncommented.
To check the version of Python installed (in case they have Python 3 for some reason), run `python -V` from the **Terminal**.

NOTE: If using Python3, pip is called pip3, and Tkinter is called tkinter. You'll also have to change the `.command` file to call `python3` instead of just `python`.

Install `pip`. You can download the `get-pip.py` from this site [here](https://packaging.python.org/tutorials/installing-packages/). Then `cd` to the location of the `get-pip.py` and run `python get-pip.py`. If any errors occur, run `sudo python get-pip.py`. The user of the machine will need to enter their password, which won't show up in the **Terminal** while being typed.

Once pip is installed, install pandas. Just run `pip install pandas` from the **Terminal**. If there are errors, try `sudo -H pip install pandas`. If it complains about numpy, run `sudo -H pip install pandas --ignore-installed`.

Check to see if they have Tkinter installed. Run `python` from the **Terminal**, then type `import Tkinter`. If no errors are displayed, then Tkinter is installed. I found that Tkinter was installed for me on macOS 10.12, but it wasn't on 10.10. There are `.pkg` files from the Python/ActiveTCL website for install Tkinter.

Make a file called `runMe.command` file in the same folder as `fys-assignment.py` and `assign`, which should look like this:

```
cd -- "$(dirname "$BASH_SOURCE")"
python fys_assignment.py
```

## Installing on a Windows Machine
----
Get Python 3 installed from [the Python website](https://www.python.org/downloads/). When running the installer, be sure to install Tkinter and pip through the advanced options/customize install.

Once installed, open up the command line and run `pip install pandas`.

The fys-assignment.py will need to have the python 2 `import` statements commented out and the python 3 `import` statements uncommented.

Make a file called `runMe.cmd` file (equivalent of `.command` file on Mac) in the same folder as `fys-assignment.py` and `assign.exe`, which should look like this:
```
cd %~dp0
python fys_assignment.py
```

## Building `assign`
----
Wherever you end up compiling, you'll need to get [dlib](https://github.com/davisking/dlib). Either clone or download the the entire library into another folder called `dlib`. You should have a directory tree that looks like this:
```
.
├── assign
├── assign.h
├── console.cpp
├── course.h
├── dlib
│   ├── appveyor.yml
│   ├── CMakeLists.txt
│   ├── dlib
│   │   ├── algs.h
│   │   ├── all
│   │   │   └── source.cpp
│   │   ...
|   ...
├── fys_assignment.py
├── Makefile
├── parser.h
├── README.md
└── student.h
```
### Mac

`¯\_(ツ)_/¯`

I didn't build the `assign` binary file, so I don't know how to on a Mac. My best guess would be to get XCode or some kind of C++ compiler and use the Makefile by running `make` in the directory.

### Windows

Download and install the [Windows C++ Build Tools](http://go.microsoft.com/fwlink/?LinkId=691126). When running the installer, be sure to install the SDK for the version of Windows it's going to be run on (I installed Windows 10). Open the **Visual C++ 2015 x86 Native Tools Command Prompt** and `cd` to the directory where the Makefile is located. To run the Makefile in Windows, use the command `nmake`. Then use this modified Makefile here (this one is ONLY FOR WINDOWS):
```
CC = cl         # compile using ms cl
CFLAGS = -O2    # optimize a lot
TARGET = assign.exe # the binary to build

all: $(TARGET)

$(TARGET): assign.h console.cpp course.h parser.h student.h
	$(CC) -Fe$(TARGET) $(CFLAGS) -Idlib console.cpp

clean:
	$(RM) $(TARGET)
```
