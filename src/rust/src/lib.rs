use polars::prelude::*;
use polars_arrow::bitmap::Bitmap;

use savvy::{r_println, savvy, ListSexp, LogicalSexp, RealSexp, StringSexp};
use savvy::{IntegerSexp, NotAvailableValue};

struct P01DataFrame(DataFrame);

#[savvy]
impl P01DataFrame {
    fn new(x: ListSexp) -> Self {
        let serieses: Vec<Series> = x
            .iter()
            .flat_map(|(k, v)| match v.into_typed() {
                savvy::TypedSexp::Integer(i) => Some(new_from_integer(k, i)),
                savvy::TypedSexp::Real(r) => Some(new_from_real(k, r)),
                savvy::TypedSexp::String(s) => Some(new_from_string(k, s)),
                savvy::TypedSexp::Logical(l) => Some(new_from_logical(k, l)),
                // TODO
                // savvy::TypedSexp::List(_) => todo!(),
                // TODO
                _ => None,
            })
            .collect();

        // TODO: support the return type savvy::Result<Self>
        // let df = DataFrame::new(serieses).map_err(|e| savvy::Error::new(&e.to_string()))?;

        let df = DataFrame::new(serieses).unwrap();

        Self(df)
    }

    fn print(&self) -> savvy::Result<()> {
        r_println!("{:?}", self.0);
        Ok(())
    }
}

fn new_from_integer(name: &str, values: IntegerSexp) -> Series {
    let values_vec = values.to_vec();
    let validity = Bitmap::from_trusted_len_iter(values_vec.iter().map(|x| !x.is_na()));

    Int32Chunked::from_vec_validity(name, values_vec, Some(validity)).into_series()
}

fn new_from_real(name: &str, values: RealSexp) -> Series {
    let values_vec = values.to_vec();
    let validity = Bitmap::from_trusted_len_iter(values_vec.iter().map(|x| !x.is_na()));

    Float64Chunked::from_vec_validity(name, values_vec, Some(validity)).into_series()
}

// StringChunked's from_vec_validity() requires numeric vector for some reason,
// so this is implemented differently
fn new_from_string(name: &str, values: StringSexp) -> Series {
    StringChunked::from_iter_options(
        name,
        values
            .iter()
            .map(|s| if s.is_na() { None } else { Some(s) }),
    )
    .into_series()
}

// BooleanChunked's from_vec_validity() requires numeric vector for some reason,
// so this is implemented differently
fn new_from_logical(name: &str, values: LogicalSexp) -> Series {
    BooleanChunked::from_iter_options(
        name,
        values
            .as_slice_raw()
            .iter()
            .map(|s| if s.is_na() { None } else { Some(*s == 1) }),
    )
    .into_series()
}
