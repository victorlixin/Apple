Notes on the iTunes LP example
=================================

The example provides an iTunes LP with the following features:

- a Home screen
- a Photos screen with a sliding list of images
- a Videos screen that shows thumbnails
- Liner Notes and Credits screens with scrolling content
- a Song List screen
- a Lyrics screen for each song

Quick start
-----------

Here's how you can quickly adapt this example to create an iTunes LP.

- Create an icon for the iTunesArtwork file.

- Edit the manifest.xml and iTunesMetadata.plist files.

- Design the seven screens: Home, Song List, Lyrics, Photos, Videos, Liner
  Notes, Credits.

- Design an extremely large image to be used as the "bleed" (the overflow
  around the 1280x720px main screen area). Replace images/interface/bleed.png
  with your image. If you are changing the file type (to JPG) make sure
  you also change the reference to the file in the CSS.

- Replace the background images in the appropriate directories under
  images/screenname/background.jpg.

- Edit controllers/data.js to add your own background audio loop, as well as
  the number of photos, links to videos, and the details on the songs within
  the album.

- Design interface elements for any navigable elements on the screens (e.g.
  home, back, arrows, play, etc). Also note that anything which is interactive
  should have two images - one for the active and one for the non-active
  state. You should be able to find all such images by looking in the package.

- Don't worry too much if you need to create images that are not exactly
  the same size as the existing template. You'll edit the CSS for each
  screen to position the images anyway. However, you should ensure that
  the active and non-active images are the same size, or they will appear
  to move as they gain focus.

- Now it is time to start editing the CSS. For UI buttons, the style 
  is completely controlled by the CSS corresponding to the page. Some
  interactive elements, such as the photos sliders and page controls,
  are styled partly by CSS and partly by Javascript. For example, the
  scaling effect seen in the photos screen is found in CSS, but the
  distance between adjacent images is defined in Javascript. In most
  cases it should be fairly clear what each property is doing - but
  make sure you look at the slidingViewData and pageControlData in Javascript.
