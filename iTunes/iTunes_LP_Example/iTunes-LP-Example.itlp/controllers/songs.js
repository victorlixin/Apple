
/* ==================== SongList Controller ==================== */

var songsController = new TKController({
  // the id in the DOM for this object, or the id for the html file if not already in the DOM
  id: 'songs',
  // back button for navigation
  backButton : '.home',
  highlightedElement: '#song01'
});

/* ==================== View Management ==================== */

songsController.viewDidLoad = function () {
  // hook up the actions
  var songActions = [];
  for (var i = 0; i < appData.songs.length; i++) {
    var padded_index = (i < 9) ? '0' + (i+1) : (i+1);
    songActions.push({
      selector: '#song' + padded_index,
      action: 'showSong',
      arguments: [i]
    });
  }
  this.actions = songActions;
};

songsController.showSong = function (index) {
  lyricsController.showWithSongAtIndex(index);
};
