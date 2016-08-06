var editor = process.env.EDITOR || 'vi';

var child = require('child_process').spawn;
hexo.on('new', function(data){
 child(editor, [data.path], {
     stdio: 'inherit'});
  });


