// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.js                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/07 13:10:04 by scollet           #+#    #+#             //
//   Updated: 2017/10/07 13:59:09 by scollet          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

const {app, BrowserWindow} = require('electron')
const url = require('url')
const path = require('path')

let win

function createWindow () {
  win = new BrowserWindow({width: 1300, height: 1100, frame: false, resizable: false})
  win.loadURL(url.format({
    pathname: path.join(__dirname, 'index.html'),
    protocol: 'file:',
    slashes: true
  }))
}

app.on('ready', createWindow)
