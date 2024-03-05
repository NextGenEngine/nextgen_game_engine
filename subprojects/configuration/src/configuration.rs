pub trait Inter {
    fn hello();
}

pub struct MyInter;

impl Inter for MyInter {
    fn hello() {
        println!("NextGen Game Configuration library");
    }
}
