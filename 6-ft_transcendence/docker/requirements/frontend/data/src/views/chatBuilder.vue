<template>
  <div class="home">
    <BlackSection class="black-section">
    <h1 class="title">Welcome to the chat </h1>
    <div class="app">
      <div ref="messages" class="messages">
        <MessageBubble
          v-for="message in messages"
          :key="message.id"
          :class="['message', { right: message.isMine }]"
          :dark="message.isMine"
          :text="message.text"
          :author="message.author"
        />
      </div>
    <ChatBox class="chat-box" @submit="onSubmit" ref="chatBox"/>
  </div>
    </BlackSection>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import BlackSection from '../components/general/BlackSection.vue'
import MessageBubble from '../components/chat/MessageBubble.vue'
import ChatBox from '../components/chat/ChatBox.vue'

interface Message {
  id: number;
  text: string;
  author: string;
  isMine: boolean;
}

export default defineComponent({
  components: {
    BlackSection,
    MessageBubble,
    ChatBox
  },
  // data array for testing purposes:
  data () {
    return {
      messages: [] as Message[],
      user: {
        name: 'Thirza' // Set the default name for the user
      }
    }
  },
  created () {
    this.getChat()
  },
  methods: {
    getChat () {
    // Simulate retrieving chat messages from the backend
      const dummyData: Message[] = [
        {
          id: 1,
          text: 'Hello',
          author: 'User1',
          isMine: false
        },
        {
          id: 2,
          text: 'Hi there!',
          author: 'User2',
          isMine: false
        }
      ]

      this.messages = dummyData
    },
    onSubmit (event: Event, text = '') {
      event.preventDefault()

      const trimmedText = text.trim() // Trim the input text

      if (trimmedText !== '') {
        const newMessage = {
          id: Date.now(), // Generate a unique ID for the message
          text,
          author: this.user.name,
          isMine: true // Assuming the current user is the author
        }
        this.messages.push(newMessage)
      }

      // Clear the text input
      (this.$refs.chatBox as typeof ChatBox).text = ''
    }
  }
})
</script>

<style scoped>

.app {
  height: 100vh;
  display: flex;
  flex-direction: column;
}

.messages {
  flex-grow: 1;
  overflow: auto;
  padding: 1rem;
  max-height: 50vh;
}

.message + .message {
  margin-top: 1rem;
}

.message.right {
  margin-left: auto;
}

.title {
  margin: 4rem 0;
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-top: 2rem; /* Add top margin */
}

.home {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.black-section {
  height: 78vh; /* Adjust the value as needed */
}

</style>
