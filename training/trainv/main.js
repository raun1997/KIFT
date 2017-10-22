// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.js                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/07 13:10:04 by scollet           #+#    #+#             //
//   Updated: 2017/10/22 12:06:14 by scollet          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

/* This just works */

var record = require('node-record-lpcm16')
var fs = require('fs')

var file = fs.createWriteStream('./train0.wav', { encoding: 'binary' })

record.start({
  sampleRate: 44100,
  verbose: true
})
.pipe(file)
