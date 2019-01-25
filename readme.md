# Conway's Game of Life

The Game of Life is a simulation originally conceived by the British mathematician J. H. Conway in 1970 and
popularized by Martin Gardner in his Scientific American column. The game models the life cycle of bacteria using a two-dimensional grid of cells. Given an initial pattern, the game simulates the birth and death of future generations of cells using a set of simple rules. In this assignment you will implement a simplified version of Conway's simulation and a basic user interface for watching the bacteria grow over time.  

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
QT Creator
```

### Installing (Bash Terminal)

In the command line within your desired directory, run the following command to download the program:

```
#Downloads the project directory to the current working directory
git clone https://github.com/venGaza/gameOfLife
```

### Opening the game
Open the project. In Qt Creator, choose "File" → "Open File or Project..." or press Ctrl+O (or Command+O on Mac). Navigate to the sample-project folder and open the file Life.pro.


### Building the game

Now you should be able to Build (Ctrl+B or Command+B) your project in Qt Creator. If it builds properly, your C++ compiler and the Stanford C++ libraries are at least compiling properly. The first time you build a given project, it will take a while (30-60 sec or more) to compile all of the various libraries. You can click the bottom "4 Compile Output" tab if you want to see the progress as it is compiling. (Recommended: In Qt Creator, click Tools → Options → Build & Run, and check the box labeled "Open Compile Output pane when building" to always see this output during compilation.)

### Run the game

Now that it's built, you should be able to Run (Ctrl+R or Command+R) your sample-project. If it runs properly, you will see a window appear with a smiley face. Congratulations, you're done! Now your machine should work just fine for working on our homework assignments.

### Errors compiling the game

Most random Qt Creator issues can be resolved by "re-initializing" your project. Here are the steps to re-initialize a project. 

```
Close Qt Creator.

Use your file explorer to navigate to the folder where your project is stored. Delete the .pro.user file that is there, such as Life.pro.user. (Note: Do not delete the .pro file, such as Life.pro; only the .pro.user file.) (screenshot)

Also delete the "build" folder for your project. This is located in the parent directory of your project's directory, and it usually has a long name like build-Life-Desktop_Qt_5_9_1_MinGW_32bit-Debug . Delete this entire build directory. (screenshot)

Re-open your project's .pro file in Qt Creator. It should ask you to "Configure Project".
Now try to re-compile and re-run your project and see if things work any better.
```

## Built With

* [Qt](https://www.qt.io/qt-features-libraries-apis-tools-and-ide/) - Qt Creator is a cross-platform C++, JavaScript and QML integrated development environment
* [Vim](https://www.vim.org/) - Vim is a highly configurable text editor for efficiently creating and changing any kind of text.

## Authors

* **Dustin Jones** - [venGaza](https://github.com/venGaza)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Stanford (https://web.stanford.edu/dept/cs_edu/qt-creator/qt-creator-linux.shtml)
* Stanford CS106B