window.onload = function() {
  document.getElementById('switch').onchange = function(ev) {
    console.log('toggle changed', ev.target.checked);
    fetch('api/led/toggle');
  };
};
