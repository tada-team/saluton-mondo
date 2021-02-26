'use strict'

const revert = require('./revert/string')

process.stdin
    .on('data', (data) => {
        process.stdout
            .write(revert(data.toString()))
    })
