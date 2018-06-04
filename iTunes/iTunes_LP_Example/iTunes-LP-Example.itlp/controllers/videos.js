
var videosHelper = {};

videosHelper.makeTab = function (tabIndex) {
  var tab = new TKController({
    id: 'video-tab-' + tabIndex
  });

  // view contents
  tab.viewDidLoad = function () {
    var padded_index = (tabIndex < 10) ? '0' + tabIndex : tabIndex;
    tab.view.appendChild(document.createElement('img')).src = 'images/videos/thumb' + padded_index + '.png';
    tab.view.className = 'video-tab';
  };

  return tab;
};

/* ==================== Videos Controller ==================== */

var videosController = new TKTabController({
  id: 'videos',
  backButton: '.home',
  tabsSelector: '.videos > div',
  controllers: [
    videosHelper.makeTab(1),
    videosHelper.makeTab(2)
  ],
  actions: [
    { selector: '.play', action: 'playSelectedVideo' }
  ],
  backButton : '.home'
});

videosController.playSelectedVideo = function () {
  if (appData.videos[this.selectedIndex].XID) {
    bookletController.play(appData.videos[this.selectedIndex]);
  } else {
    bookletController.playNonLibraryContent(appData.videos[this.selectedIndex]);
  }
};

videosController.tabAtIndexWasActivated = function (index) {
  this.playSelectedVideo();
};
