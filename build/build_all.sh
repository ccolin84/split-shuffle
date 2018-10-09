rm -rf bin/*
sh build/build_create_sample_input.sh
sh build/build_split_shuffler.sh
sh build/build_run_split_shuffle.sh
sh build/build_tests.sh
rm bin/*.o 