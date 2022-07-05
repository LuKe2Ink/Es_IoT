const { app, BrowserWindow } = require('electron')

function createWindow() {
  const win = new BrowserWindow({
    // icon: getPathIcon(),
    autoHideMenuBar: true,
    alwaysOnTop: true,
    width: 500,
    height: 500,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
    },
  })
  ////win.openDevTools();
  
  win.loadFile('./vaffa.html');

  win.openDevTools()
//   win.on('close', function (event){
//     event.preventDefault();
//     win.hide();
//     client.start();
//   })

  /*child = new BrowserWindow({parent: win,transparent:true});
      child.show();*/
}

app.whenReady().then(()=>{
    createWindow();
    app.on('activate', function () {
        if (BrowserWindow.getAllWindows().length === 0) createWindow()
      })
  })