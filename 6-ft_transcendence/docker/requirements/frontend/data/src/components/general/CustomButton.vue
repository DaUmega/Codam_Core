
<template>
  <button class="custom-button" @click="handleClick">
    <slot></slot>
  </button>
</template>

<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
  props: {
    handleClick: {
      type: Function,
      required: true
    }
  }
})
</script>

<style scoped>
.custom-button {
  background-color: grey; /* Change the background color to grey */
  color: white; /* Change the text color to white */
  padding: 4px 10px; /* Adjust padding to standardize button sizes */
  border: none; /* Remove button border */
  border-radius: 4px; /* Apply border radius to round the button corners */
  cursor: pointer; /* Change the cursor to a pointer on hover */
}

.custom-button:hover {
  background-color: darkgrey; /* Change the background color to dark grey on hover */
}
</style>
