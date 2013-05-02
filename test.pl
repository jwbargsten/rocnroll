#!/usr/bin/env perl

use warnings;
use strict;
use 5.010;

open my $fh, '<', "../2013-04-26/prediction.cv.go.ag2bmrf.tsv" or die "Can't open filehandle: $!";

my %data;
while(my $l = <$fh>) {
  chomp $l;
  my @row = split /\t/, $l;
  $data{$row[0]} //= [];
push @{$data{$row[0]} }, \@row;
}

my $z = $data{"cv44"};

for my $s (@$z) {
  say join(" ", @$s);
}
