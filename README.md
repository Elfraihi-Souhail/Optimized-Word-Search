# Word-Optimized Search Using BST Variants

## Project Overview

This project implements an **optimized word search system** using three specialized Binary Search Tree (BST) variants, each designed to handle different categories of words for maximum search efficiency. The system demonstrates how custom BST implementations can significantly improve search performance compared to a standard BST approach.

## Key Features

### 1. Specialized BST Variants

The system implements three BST variants, each optimized for different word categories:

- **BST-1**: Optimized for words starting with **X, Y, or Z**
  - Uses rotation to bring matching words toward the root during insertion
  - Ideal for scientific terms, proper nouns, and rare starting letters

- **BST-2**: Optimized for words starting with **letters after 'a'** (b-z)
  - Applies different rotation strategies based on word characteristics
  - Handles the majority of common English words

- **BST-3**: Optimized for **all other words**
  - Catches words not handled by the first two variants
  - Uses rotation for non-X/Y/Z words

### 2. Intelligent Word Routing

The system automatically routes search operations to the appropriate BST based on the first character of the search term:

```c
if word starts with X, Y, or Z → Search in BST-1
else if word starts with letter after 'a' → Search in BST-2  
else → Search in BST-3
```

### 3. Performance Optimization Techniques

- **Rotation strategies**: Each BST uses different rotation approaches during insertion to maintain balance for their specific word categories
- **Specialized traversal**: Efficient inorder traversal with color-coded output based on word categories
- **Level-based analysis**: Display words by tree level with statistical information

### 4. Efficiency Simulation Framework

The project includes a comprehensive simulation system to measure and compare:

- **Word search efficiency**: Compares path lengths between standard BST and the triplet approach
- **Range search efficiency**: Measures performance for finding all words between two given words
- **Statistical analysis**: Calculates efficiency ratios and provides visual results

## Technical Implementation

### Data Structures

- **Specialized BST nodes** with parent pointers for efficient rotation
- **Queue structures** for level-order traversal and analysis
- **File management system** with open file tracking

### Algorithms

- **Rotation algorithms**: Left and right rotations for tree balancing
- **Search algorithms**: Optimized search for each BST variant
- **Range search**: Efficient inorder traversal between two words
- **Statistical analysis**: Path length measurement and efficiency comparison

### Color-Coded Visualization

The system uses ANSI color codes to visually distinguish word categories:

- 🔴 **Red**: Words starting with X, Y, or Z
- 🟢 **Green**: Words starting with letters after 'a'
- 🟡 **Yellow**: All other words

## Performance Benefits

The optimized approach provides several advantages over a standard BST:

1. **Reduced search path length** for categorized words
2. **Better balance** through category-specific rotation strategies
3. **Efficient memory usage** by separating word categories
4. **Faster range queries** through specialized traversal

## Usage Examples

### 1. Efficient Word Search

```c
// Search for "Xylophone" - automatically routed to BST-1
Single_word_search(&Bst1, &Bst2, &Bst3, "Xylophone", &Result);

// Search for "Apple" - automatically routed to BST-2  
Single_word_search(&Bst1, &Bst2, &Bst3, "Apple", &Result);
```

### 2. Range Search Optimization

```c
// Find all words between "Apple" and "Zebra"
// System uses the most efficient traversal for each segment
Range_search(&Bst1, &Bst2, &Bst3, "Apple", "Zebra");
```

### 3. Performance Analysis

```c
// Compare search efficiency between standard BST and optimized approach
SimulateWordSearch(10, 10000); // 10 trials with 10,000 words each

// Analyze range search performance  
SimulateRangeSearch(10, 10000); // 10 trials with 10,000 words each
```

## Academic Significance

This project demonstrates several important computer science concepts:

1. **Algorithm optimization** through problem-specific data structures
2. **Tree balancing techniques** and their impact on search performance
3. **Empirical analysis** of algorithm efficiency through simulation
4. **Memory vs. performance tradeoffs** in data structure design


## Example Usage

1. Generate a file with 1000 random words
2. Build the three BST variants
3. Search for words starting with "X"
4. Perform a range search from "Apple" to "Zebra"
5. Run efficiency simulations with M=10, N=10000

## Limitations

- Maximum word length: 255 characters
- File-based operations may be slow for very large datasets
- Color coding may not work on all terminal emulators
 
## Conclusion

This word-optimized search system showcases how specialized BST variants can significantly improve search performance for categorized data. By separating words based on their starting characters and applying appropriate optimization strategies, the system achieves better performance than a standard BST approach while maintaining all BST operations and properties.

The project provides a practical framework for evaluating data structure efficiency and demonstrates the value of custom data structures for specific problem domains.


## Author

Developed as part of an academic project by Sidali BEGGAR and Souhail ELFRAIHI, based on the Translation Z to C framework by Pr. D.E ZEGOUR.

## License

Academic use - Copyright 2014, ESI - Algier
