use rand::seq::SliceRandom;
use rand::thread_rng;
use std::io::{stdin, Read};

fn shuffle_words(stdin_buf: &String) {
    let mut rng = thread_rng();

    let mut word_buffer = String::new();

    let mut is_accumulating_word = false;

    for single_char in stdin_buf.chars() {
        let is_break_char = single_char.is_whitespace() || single_char.is_ascii_punctuation();
        if is_break_char && is_accumulating_word {
            let mut char_vec = word_buffer.chars().collect::<Vec<char>>();

            let char_vec_len = char_vec.len();
            if char_vec_len > 1 {
                let chars_to_shuffle = &mut char_vec[1..(char_vec_len - 1)];

                chars_to_shuffle.shuffle(&mut rng);
                let shuffled_word = char_vec.iter().collect::<String>();

                print!("{}", shuffled_word);
            }
            else if char_vec_len == 1
            {
                print!("{}", char_vec[0]);
            }

            word_buffer.clear();
            print!("{}", single_char);
        } else if !is_break_char && is_accumulating_word {
            word_buffer.push(single_char);
        } else {
            is_accumulating_word = true;
            print!("{}", single_char);
        }
    }
    println!();
}

fn main() {
    let mut stdin_buf = String::new();
    {
        let mut stdin = stdin();
        stdin
            .read_to_string(&mut stdin_buf)
            .expect("Could not read stdin");
    }

    shuffle_words(&stdin_buf);
}
