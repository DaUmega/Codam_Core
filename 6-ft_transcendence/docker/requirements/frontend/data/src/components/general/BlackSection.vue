<template>
  <div class="black-section">
    <slot></slot> <!-- Content passed to the slot will be inserted here -->
  </div>
</template>

<style scoped>
.black-section {
  background-color: black;
  padding: 20px;
  border-radius: 10px;
  color: white; /* Add color for the text to be visible */
  box-shadow: 0px 0px 10px 5px rgba(128, 128, 128, 0.5); /* Add a grey box shadow for the 3D effect */
}
</style>
