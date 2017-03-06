# Overview
Scallop is an accurate reference-based transcript assembler. Scallop features
its high accuracy in assembling multi-exon transcripts as well as lowly
expressed transcripts. Scallop achieves this improvement through a novel
algorithm that unifies multiple objectives into a single optimization
framework.

# Installation
To install Scallop, you need to first download/compile a few software packages
(htslib, Boost, and GUROBI), setup the corresponding environmental variables,
and then compile the source code of Scallop.

## Install htslib
Download htslib [(license)](https://github.com/samtools/htslib/blob/develop/LICENSE)
from (http://www.htslib.org/) with version 1.2 or higher.
Compile it to generate the htslib file `libhts.a`. 
Set environment variable `HTSLIB` to indicate the directory of `libhts.a`.
For example, for Unix platforms, add the following statement to the file `~/.bash_profile`:
```
export HTSLIB="/directory/to/your/htslib/htslib-1.2.1"
```

## Install Boost
Download Boost [(license)](http://www.boost.org/LICENSE_1_0.txt)
from (http://www.boost.org).
Uncompress it somewhere (compiling and installing are not necessary).
Set environment variable `BOOST_HOME` to indicate the directory of Boost.
For example, for Unix platforms, add the following statement to the file `~/.bash_profile`:
```
export BOOST_HOME="/directory/to/your/boost/boost_1_60_0"
```

## Install GUROBI
Download GUROBI from (http://www.gurobi.com/) and uncompress the package
somewhere (compiling and installing are not required).  You need to apply an
academic license to use the full features of GUROBI (Please refer to the GUROBI
documentation for more information.) After that, set two environment
variables, `GUROBI_HOME` and `GRB_LICENSE_FILE`, which indicates the directory
of GUROBI, and the location of your license file, respectively.  For example,
for Unix platforms, add the following two statements to the file `~/.bash_profile`:
```
export GUROBI_HOME="/directory/to/your/gurobi/linux64"
export GRB_LICENSE_FILE="/location/of/your/license/gurobi.lic"
```
## Compile Scallop
Run the script `build.sh`, which will generate the executable file `src/src/scallop`.


# Usage

The usage of `scallop` is:
```
./scallop -i <input.bam> -o <output.gtf> [options]
```

The `input.bam` is the read alignment file generated by some RNA-seq aligner, (for example, TopHat2, STAR, or HISAT2).
Make sure that it is sorted; otherwise run `samtools` to sort it:
```
samtools sort input.bam > input.sort.bam
```

The reconstructed transcripts shall be written as gtf format into `output.gtf`.

Scallop support the following parameters:

Parameters | Default Value | Description
------------ | ------------- | ----------
 --library_type               | unstranded | chosen from {first, second, unstranded}
 --min_transcript_coverage    | 1.01 | the minimum coverage required to output a multi-exon transcript
  --min_single_exon_coverage   | 20 | the minimum coverage required to output a single-exon transcript
 --min_exon_length            | 50 | the minimum length of a transcript is: --min_transcript_length <br> + --min_exon_length * num-of-exons
 --min_transcript_length      |250 | the minimum length of a transcript is: --min_transcript_length <br> + --min_exon_length * num-of-exons
 --min_mapping_quality        | 1 | ignore reads with mapping quality less than this value
 --min_bundle_gap             |50 | the minimum distances required to start a new bundle
 --min_num_hits_in_bundle     | 20 | the minimum number of reads required in a bundle
 --min_flank_length           | 3 | the minimum match length required in each side for a spliced read
 --min_splice_bundary_hits    | 1 | the minimum number of spliced reads required to support a junction