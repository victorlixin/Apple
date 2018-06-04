
/* ==================== Lyrics Controller ==================== */

var lyricsController = new TKLyricsController({
  id: 'lyrics',
  actions : [
    { selector: '.play', action: 'playCurrentSong' }
  ],
  outlets : [
    { name: 'container', selector: '.lyrics-container' }
  ],
  backButton: '.songs',
  highlightedElement: '.play',
  scrollableElement : '.lyrics-container',
  numberOfSongs: appData.songs.length,
  previousSongButton: '.left-arrow',
  nextSongButton: '.right-arrow'
});

/* ==================== Creating Pages ==================== */

lyricsController.songDidChange = function (songIndex) {
  // clean up the container and reset scroll offset
  this.container.textContent = '';
  this.container.scrollTop = 0;
  var padded_index = (songIndex < 9) ? '0' + (songIndex+1) : (songIndex+1);
  this.container.appendChild(document.createElement('img')).src = 'images/songs/lyrics' + padded_index + '.jpg';
};

/* ==================== Jumping to a song ==================== */

lyricsController.showWithSongAtIndex = function (index) {
  bookletController.navigation.pushController(this);
  this.currentSong = index;
};

/* ==================== Actions ==================== */

lyricsController.playCurrentSong = function () {
	bookletController.play(appData.songs[this.currentSong]);
};

lyricsController.preferredElementToHighlightInDirection = function (currentElement, direction) {
  return (currentElement.hasClassName('right-arrow') && direction == KEYBOARD_LEFT) ? this.view.querySelector('.left-arrow') : undefined;
};
