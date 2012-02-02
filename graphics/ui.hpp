#include "scene.hpp"

struct SDL_Surface;

struct Ui {

	Ui(unsigned int width, unsigned int height);

	// run runs the Ui at the given frame rate.
	void run(unsigned long);

	// scene is called once per frame to get the current scene.
	// The viewport is scaled so that the lower left corner is
	// (0,0) and the upper-right corner is (width, height).  The
	// scene must be scaled/moved to fit within this coordinate
	// system.
	virtual void scene(Scene &);

	// key is called everytime a key is pressed or released.
	// The first argument is the key code (from SDL).
	// If the key is pressed then the second argument is
	// true otherwise it is false.
	virtual void key(int, bool);

	// motion is called whenever the mouse moves.
	// The first two arguments are the absolute coordinates
	// of the new cursor position.  The second two arguments
	// are the relative coordinates of the new position with
	// respect to the previous.
	virtual void motion(int, int, int, int);

	// click is called whenever the mouse is clicked.
	// The first arguments are the location of the click.
	// The third argument is the number of the button that
	// was pressed and the final argument is true if the
	// click was a down-click and is false if the click
	// was an up-click.
	virtual void click(int, int, int, bool);

private:

	// handleevents handles events and returns
	// true if it is time to quit.
	bool handleevents(void);

	unsigned int width, height;
	SDL_Surface *screen;
};