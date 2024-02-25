#[macro_export]
macro_rules! map_error {
    ($result:expr, $error_varriant:path) => {
        $result.map_err(|_err| $error_varriant)
    };
}

#[macro_export]
macro_rules! log {
    ($file:expr, $($arg:tt)*) => {
        writeln!($file, $($arg)*).expect("Failed to write to log file.")
    };
}
