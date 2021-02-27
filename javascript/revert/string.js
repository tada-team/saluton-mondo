'use strict'

const shuffleWord = word => {
    if (word.length <= 3) {
        return word
    }

    const middle = word.substr(1, (word.length-2))
        .split('')

    middle.sort(() => (Math.random() - 0.5))

    return [
            word.substr(0, 1),
            middle.join(''),
            word.substr(word.length-1, 1)
        ].join('')
}

module.exports = (string) => {
    let buffer = ''

    return String(string).split('')
        .map(char => {
            if (!/[\s\-\_\:\;\,\.]/.test(char)) {
                buffer += String(char)
                return
            }

            const word = shuffleWord(buffer) + char
            buffer = ''

            return word
        })
        .join('')
}
