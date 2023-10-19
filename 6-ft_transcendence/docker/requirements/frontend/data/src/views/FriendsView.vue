<template>
  <div class="home">
    <div class="spacing"></div>
    <BlackSection>
      <div class="friends">
        <h1 class="title">Your friends</h1>
        <ul class="friend-list">
          <router-link
            v-for="(friend, index) in friends"
            :key="index"
            :to="`/profile?user=${friend.login}`"
          >
            <template v-slot="{ navigate, href }">
              <li class="friend-entry" @click="navigate" :href="href">
                {{ friend.login }} - {{ friend.nickname }}, Status: {{ showStatus(friend.currentStatus) }}
              </li>
            </template>
          </router-link>
        </ul>
      </div>
    </BlackSection>
    <div class="incoming-requests" v-if="incomingRequests.length > 0">
      <h2 class="small-title">Incoming Friend Requests</h2>
      <ul>
        <li v-for="(request, index) in incomingRequests" :key="index">
          {{ request.login }} wants to be your friend
          <CustomButton class="accept-button" :handleClick="() => acceptFriendRequest(request)">Accept</CustomButton>
          <CustomButton class="reject-button" :handleClick="() => rejectFriendRequest(request)">Reject</CustomButton>
        </li>
      </ul>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import BlackSection from '../components/general/BlackSection.vue'
import CustomButton from '../components/general/CustomButton.vue'
import { API } from '@/plugins/axios'

const activeUser = sessionStorage.getItem('activeuser')

export default defineComponent({
  name: 'FriendsPage',
  components: {
    BlackSection,
    CustomButton
  },
  data () {
    return {
      friends: [],
      incomingRequests: []
    }
  },
  methods: {
    async parseUsername () {
      const urlParams = new URLSearchParams(window.location.search)
      const username = urlParams.get('user')

      if (activeUser) {
        await API.get(`updateUserActivity/${activeUser}/1`)
      }
      if (username) {
        try {
          const response = await API.get(`login?user=${username}`)
          const friendResponse = await API.get(`friend/friend-list?id=${response.data.id}`)
          const friendRequests = await API.get(`friend/friend-request?id=${response.data.id}`)

          console.log('requests:', friendRequests.data)
          this.friends = friendResponse.data
          this.incomingRequests = friendRequests.data
        } catch (error) {
          console.error('Internal Error:', error)
        }
      }
    },
    async acceptFriendRequest (request: { id: string }) { // TODO: IS THIS A STRING OR?
      console.log('Accepting friend request from:', request.id)
      try {
        const getId = await API.get(`login?user=${activeUser}`)
        console.log('debug:', getId.data.id)
        const response = await API.post('friend/edit-friend', {
          userId: getId.data.id,
          friendId: request.id,
          action: 0
        })

        if (response.status === 201) {
          window.location.reload()
        }
      } catch (error) {
        console.error('Error Adding Friend:', error)
      }
    },
    async rejectFriendRequest (request: { id: string }) {
      console.log('Rejecting friend request from:', request.id)
      try {
        const getId = await API.get(`login?user=${activeUser}`)
        const response = await API.post('friend/edit-friend', {
          userId: getId.data.id,
          friendId: request.id,
          action: 3
        })

        if (response.status === 201) {
          window.location.reload()
        }
      } catch (error) {
        console.error('Error Adding Friend:', error)
      }
    },
    showStatus (currentStatus: number) {
      if (currentStatus === 1) {
        return 'Online'
      } else if (currentStatus === 2) {
        return 'Offline'
      } else if (currentStatus === 3) {
        return 'In a Game'
      } else {
        return ''
      }
    }
  },
  created () {
    this.parseUsername()
  }
})
</script>

<style scoped>
.home {
  min-height: 100vh;
  position: relative;
  display: flex;
  flex-direction: column;
  justify-content: flex-start; /* Align items at the top */
  align-items: center;
}

.title {
  margin: 0;
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-top: 0.5rem; /* Add top margin */
  margin-bottom: 0rem; /* Reduce the bottom margin */
}

.friends {
  margin-bottom: 1rem; /* Add margin-bottom to create spacing between sections */
}

.title.smaller {
  font-size: 15px; /* Set a smaller font size for the "Search users" title */
}

.input-group {
  display: flex;
  flex-direction: row;
  align-items: center; /* Align items vertically in the center */
  margin-bottom: 1rem; /* Reduce the margin-bottom between the title and input bar */
}

.input-group input {
  margin-right: 0.5rem; /* Add right margin to create space between input and button */
}

.friends .custom-button {
  background-color: green; /* Change color */
  padding: 7px 9px; /* Increase the padding to make the button bigger */
  font-size: 10px; /* Increase the font size of the button text */
  font-weight: bold; /* Make the button text bold */
}

.custom-button:hover {
  background-color: darkgreen; /* Change the background color on hover */
}

.spacing {
  margin-bottom: 1rem;
}

.friend-list {
  list-style: none; /* Remove default list styles */
  padding: 0; /* Remove default padding */
  display: flex;
  flex-direction: column;
  align-items: center;
}

.friend-entry {
  color: white;
  margin: 5px 0; /* Add margin between friend entries */
  text-align: center;
}

.incoming-requests, .incoming-requests h2, .incoming-requests li {
  color: white;
}
</style>
