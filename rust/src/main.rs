use rand::{random, seq::SliceRandom};
use rand_pcg::Pcg64;
use std::{
    io::{stdin, Read},
};

#[cfg(test)]
mod tests {
    use crate::shuffle_word;

    #[test]
    fn run_test() {
        assert_eq!(shuffle_word(&"а".to_string(), Some(0)), "а");
        assert_eq!(shuffle_word(&"бы".to_string(), Some(0)), "бы");
        assert_eq!(shuffle_word(&"это".to_string(), Some(0)), "это");
        assert_eq!(shuffle_word(&"это!".to_string(), Some(0)), "это!");
        assert_eq!(shuffle_word(&"что-то".to_string(), Some(0)), "что-то");
        assert_eq!(shuffle_word(&"123456789".to_string(), Some(0)), "123456789");
        assert_eq!(shuffle_word(&"какой-то".to_string(),Some(0) ), "каокй-то");
        assert_eq!(shuffle_word(&"удивительное рядом!".to_string(), Some(0)), "удинлвоетьие ряодм!");
    }
}

fn shuffle_word(original_word: &String, seed_option: Option<u128>) -> String {

    let seed: u128 = seed_option.unwrap_or(random());

    let mut rng =Pcg64::new(seed, 0xa02bdbf7bb3c0a7);
    
    let mut new_string = String::new();

    let mut word_buffer = String::new();

    let mut is_accumulating_word = false;

    for single_char in original_word.chars() {
        let is_break_char = single_char.is_whitespace() || single_char.is_ascii_punctuation();
        if is_break_char && is_accumulating_word {
            let mut char_vec = word_buffer.chars().collect::<Vec<char>>();

            let char_vec_len = char_vec.len();
            if char_vec_len > 1 {
                let chars_to_shuffle = &mut char_vec[1..(char_vec_len - 1)];

                chars_to_shuffle.shuffle(&mut rng);
                let shuffled_word = char_vec.iter().collect::<String>();

                new_string.push_str(&shuffled_word);
            } else if char_vec_len == 1 {
                new_string.push(char_vec[0]);
            }

            word_buffer.clear();
            new_string.push(single_char);
        } else if !is_break_char && is_accumulating_word {
            word_buffer.push(single_char);
        } else {
            is_accumulating_word = true;
            new_string.push(single_char);
        }
    }

    if !(word_buffer.is_empty())
    {
        new_string.push_str(&word_buffer);
    }

    return new_string;
}

fn shuffle_words(stdin_buf: &String) {
    let shuffled_line = shuffle_word(&stdin_buf, None);
    println!("{}", shuffled_line);
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
