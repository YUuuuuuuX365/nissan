# Nissan Project

This is a test repository for Codex environment.

## calculate_max_element_size

`calculate_max_element_size` computes the maximum element dimensions in a tetrahedral mesh. Pass the element connectivity and node coordinates, and it returns the largest lengths in x, y and z directions.

The file `calculate_max_element_size.c` contains a small test driver that can be compiled with:

```bash
gcc -DTEST_MAIN calculate_max_element_size.c -o test && ./test
```

