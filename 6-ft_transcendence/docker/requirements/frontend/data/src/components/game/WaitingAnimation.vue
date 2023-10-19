<template>
  <div class="waiting-animation">
    <span>Looking for a player</span>
    <span v-for="(dot, index) in dots" :key="index" class="dot">{{ dot }}</span>
  </div>
</template>

<script lang="ts">
import { defineComponent, ref } from 'vue'

export default defineComponent({
  name: 'WaitingAnimation',
  data () {
    return {
      dots: ['.', '.', '.']
    }
  }
})
</script>

<style scoped>
.waiting-animation {
  display: flex;
  align-items: center;
  color: red; /* Replace with the desired color */
  z-index: 999; /* Set a high z-index value to ensure it appears in front of other elements */
}

.dot {
  font-size: 18px;
  animation: dotAnimation 1s infinite;
  margin-left: 4px;
}

@keyframes dotAnimation {
  0% {
    opacity: 0;
  }
  50% {
    opacity: 1;
  }
  100% {
    opacity: 0;
  }
}
</style>
