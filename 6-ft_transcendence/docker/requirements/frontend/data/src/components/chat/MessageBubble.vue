<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
  name: 'MessageBubble',
  props: [
    'text', // Content of the message
    'author', // Author of the message
    'createdAt', // Timestamp of message
    'dark' // Background variant of the box
  ],
  computed: {
    formattedCreatedAt () {
      const date = new Date(this.createdAt)
      const yy = date.getFullYear().toString().slice(-2)
      const mm = (date.getMonth() + 1).toString().padStart(2, '0')
      const dd = date.getDate().toString().padStart(2, '0')
      const hh = date.getHours().toString().padStart(2, '0')
      const min = date.getMinutes().toString().padStart(2, '0')
      const ss = date.getSeconds().toString().padStart(2, '0')

      return `${yy}-${mm}-${dd} ${hh}:${min}:${ss}`
    }
  }
})
</script>

<template>
  <div
      :class='["message", { dark }]'
  >
    <h5>{{ author }}</h5>
    <p>{{ text }}</p>
    {{ formattedCreatedAt }}
  </div>
</template>

<style scoped>
.message {
  background: #71beba;
  border-radius: 10px;
  padding: 1rem;
  width: fit-content;
}

.message.dark {
  background: #328e89;
}

h5 {
  margin: 0 0 .5rem 0;
}
</style>
