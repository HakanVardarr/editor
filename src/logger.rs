use chrono::{DateTime, Utc};
use std::{
    fs::{File, OpenOptions},
    io::Write,
    time::SystemTime,
};

pub struct Logger {
    file: File,
}

impl Logger {
    pub fn new(path: &str) -> Self {
        let file = OpenOptions::new()
            .read(true)
            .write(true)
            .create(true)
            .truncate(true)
            .open(path)
            .unwrap();

        Self { file }
    }

    pub fn info(&mut self, message: &str) {
        let now = SystemTime::now();
        let datetime: DateTime<Utc> = now.into();

        let _ = self
            .file
            .write(format!("[{}](INFO):{message}\n", datetime.format("%d/%m/%Y %T")).as_bytes());
    }
}
