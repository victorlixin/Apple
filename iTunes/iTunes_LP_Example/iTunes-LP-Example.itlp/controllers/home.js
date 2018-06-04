
var albumHelper = {};

albumHelper.playAlbum = function() {
  var playlist = bookletController.buildPlaylist(appData.songs);
  playlist.play();
};

var homeController = new TKController({
  id: 'home',
  actions : [
    { selector: '.menu > .play', action: albumHelper.playAlbum }
  ],
  navigatesTo : [
    { selector: '.menu > .songs', controller: 'songs' },
    { selector: '.menu > .photos', controller: 'photos' },
    { selector: '.menu > .videos', controller: 'videos' },
    { selector: '.menu > .linernotes', controller: 'linernotes' },
    { selector: '.menu > .credits', controller: 'credits' }
  ],
  // make the PLAY button be default highlight
  highlightedElement : '.menu > .play'
});
