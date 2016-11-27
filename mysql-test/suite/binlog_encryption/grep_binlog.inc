#
# This include file checks whether the given pattern is present
# in the given binary log(s)
# The search logic returns 0 if no occurrences are found,
# and 1 otherwise. 
# The result can be reverted depending on search_result configured
# in the outer test.
#
# Usage:
#   --let search_files= filename | filename_prefix*
#   --let search_pattern= <search pattern> (default '_to_encrypt')
#   --let search_result= 0|1 (default 0, which means "should not be found")
#   --source grep_binlog.inc

if (! $search_result)
{
    --let search_result= 0
}
if (! $search_pattern)
{
    --let search_pattern= _to_encrypt
}
--let datadir= `SELECT @@datadir`

--echo #
--echo # The next step will cause a perl error if the search does not
--echo # meet the expectations. 
--echo #   Pattern to look for: $search_pattern
--echo #   Files to search:     $search_files
--echo #   Expected result:     $search_result 
--echo # (0 means the pattern should not be found, 1 means it should be found)
--echo #

--error $search_result
perl;
    $|= 1;
    use strict;
    use warnings;
    my @content= ();
    my @fnames= glob("$ENV{datadir}/$ENV{search_files}");
    if (not scalar(@fnames)) {
        die "File pattern $ENV{search_files} must be wrong, no files found\n";
    }
    foreach my $f (@fnames) {
        open(FILE, "<", $f) or die "Could not open file $f: $!\n";
        @content= (@content, grep(/$ENV{search_pattern}/, <FILE>));
        close FILE;
    }
    print( (scalar(@content) ? "Found" : "Did not find any"). " occurrences of '$ENV{search_pattern}' in $ENV{search_files}\n");
    exit (scalar(@content) ? 1 : 0);
EOF

# Unset the mandatory option
--let search_files=
