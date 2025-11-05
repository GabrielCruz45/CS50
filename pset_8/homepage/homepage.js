// function pauseOtherVideos() {
//     let video1 = document.getElementById('vid1');
//     let video2 = document.getElementById('vid2');
//     let video3 = document.getElementById('vid3');

//     video1.addEventListener('play', function() {
//         video2.pause();
//         video3.pause();
//     });

//     video2.addEventListener('play', function() {
//         video1.pause();
//         video3.pause();
//     });

//     video3.addEventListener('play', function() {
//         video1.pause();
//         video2.pause();
//     });
// }

let video1 = document.getElementById('vid1');
let video2 = document.getElementById('vid2');
let video3 = document.getElementById('vid3');

document.getElementById('gabsCarousel').addEventListener('slide.bs.carousel', function () {
    video1.pause();
    video2.pause();
    video3.pause();
  });