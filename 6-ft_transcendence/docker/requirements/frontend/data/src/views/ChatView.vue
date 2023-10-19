<template>
  <div class="chat">
    <BlackSection class="channel-section black-section">
      <div>
        <h1 class="title">Joined Channels</h1>
        <div class="title-line"></div>
        <div>
          <a
            v-for="channel in joinedChannels"
            :key="channel.id"
            href="#"
            @click.prevent="switchChannel(channel.id)"
          >
            <div class="channel-item">{{ channel.id }} - {{ channel.name }}</div>
          </a>
        </div>
      </div>
      <div>
        <h1 class="title">Public Channels</h1>
        <div class="title-line"></div>
        <div>
          <a
            v-for="channel in publicChannels"
            :key="channel.id"
            href="#"
            @click.prevent="switchChannel(channel.id)"
          >
            <div class="channel-item">{{ channel.id }} - {{ channel.name }}</div>
          </a>
        </div>
      </div>
      <div>
        <CustomButton v-if="activeUser.nickname" class="custom-button small-button default-button" :handleClick="openDialog">Create Channel</CustomButton>
      </div>
      <div v-if="createChannelDialog">
        <form @submit.prevent="submitCreateChannel">
          <div>
            <label for="channelName">Channel Name</label>
            <input v-model="newChannelData.name" type="text" id="channelName" required>
          </div>
          <div>
            <label for="channelPassword">Password (optional)</label>
            <input v-model="newChannelData.password" type="password" id="channelPassword">
          </div>
          <div>
            <label for="publicChannel">Public Channel</label>
            <input v-model="newChannelData.isPublic" type="checkbox" id="publicChannel">
          </div>
          <div>
            <CustomButton class="custom-button small-button default-button" :handleClick="createChannel">Create</CustomButton>
            <CustomButton class="custom-button small-button default-button" :handleClick="closeDialog">Cancel</CustomButton>
          </div>
        </form>
      </div>
    </BlackSection>

    <BlackSection class="general-chat-section middle-section black-section">
      <h1 class="title">Chatting in Channel: {{ currentChannel.name }}</h1>
      <div class="title-line"></div>
      <!-- Display the content of the selected channel -->
      <div class="channel-content" v-if="currentChannel">
        <div class="app">
          <div ref="messages" class="messages">
            <!-- Display chat messages for the current channel -->
            <MessageBubble
              v-for="message in currentChannel.messages"
              :key="message.id"
              :class="['message', { right: isMyMessage(message) }]"
              :dark="isMyMessage(message)"
              :text="message.text"
              :author="message.sender.nickname"
              :createdAt="message.createdAt"
            />
          </div>
          <ChatBox class="chat-box" ref="chatBox" @submit="sendMessage"/>
        </div>
      </div>
    </BlackSection>

    <!-- Players section (display user list and buttons) -->
    <BlackSection class="players-section black-section">
      <h1 class="title">Players</h1>
      <div class="title-line"></div>
      <div class="player-list">
        <div>
          <a
            v-for="member in currentChannel.members"
            :key="member.id"
            href="#"
            @click.prevent="toggleUserActions(member.id)"
          >
            <div>
              {{ member.login }} - {{ member.nickname }}
              <div class="player-actions" v-if="member.id === otherUser.id">
                <CustomButton class="custom-button small-button default-button" :handleClick="profileUser">Profile</CustomButton>
                <CustomButton class="custom-button small-button default-button" :handleClick="kickUser">Kick</CustomButton>
                <CustomButton v-if="!isBlocked" class="custom-button small-button block-button" :handleClick="blockUser">Block</CustomButton>
                <CustomButton v-if="isBlocked && isBlocker" class="custom-button small-button block-button" :handleClick="unblockUser">Unblock</CustomButton>
                <CustomButton v-if="!isBlocked" class="custom-button small-button default-button" :handleClick="sendPM">DM</CustomButton>
                <CustomButton v-if="!isBlocked" class="custom-button small-button default-button" :handleClick="challenge">Challenge</CustomButton>
                <CustomButton class="custom-button small-button default-button" v-if="isUserAdminOrOwner()" :handleClick="muteUser">Mute</CustomButton>
                <CustomButton class="custom-button small-button default-button" v-if="isUserAdminOrOwner()" :handleClick="unmuteUser">Unmute</CustomButton>
                <CustomButton class="custom-button small-button default-button" v-if="isUserAdminOrOwner()" :handleClick="banUser">Ban</CustomButton>
                <CustomButton class="custom-button small-button default-button" v-if="isUserAdminOrOwner()" :handleClick="makeAdmin">Make Admin</CustomButton>
              </div>
            </div>
          </a>
          <div class="player-actions" v-if="isUserAdminOrOwner()">
            <p>Admin Panel Below</p>
            <CustomButton class="custom-button small-button default-button" :handleClick="addUser">Add User</CustomButton>
            <CustomButton class="custom-button small-button default-button" :handleClick="unbanUser">Unban User</CustomButton>
            <CustomButton class="custom-button small-button block-button" v-if="isUserAdminOrOwner()" :handleClick="deleteChannel">Destroy Channel</CustomButton>
          </div>
          <div v-if="showPopup" class="popup-container">
            <div class="popup">
              <p>{{ popupMessage }}</p>
              <CustomButton class="custom-button small-button default-button" :handleClick="acceptChallenge">Accept</CustomButton>
              <CustomButton class="custom-button small-button default-button" :handleClick="ignoreChallenge">Ignore</CustomButton>
            </div>
          </div>
        </div>
      </div>
    </BlackSection>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import CustomButton from '../components/general/CustomButton.vue'
import BlackSection from '../components/general/BlackSection.vue'
import MessageBubble from '../components/chat/MessageBubble.vue'
import ChatBox from '../components/chat/ChatBox.vue'
import { API } from '@/plugins/axios'
import { useToast } from 'vue-toastification'
import SocketioService from '@/services/socketio.service'
import ToastPlugin from '@/plugins/toast'

const activeUser = sessionStorage.getItem('activeuser')
const siteIP = process.env.VUE_APP_SITE_IP
const apiKey = process.env.VUE_APP_SECRET
const mutedChannels = [
  {
    channelId: -1,
    muteEndTime: -1
  }
]
const tempMuted = sessionStorage.getItem('mutedchannels')
if (tempMuted) {
  const parsedMutedChannels = JSON.parse(tempMuted)
  if (parsedMutedChannels) {
    mutedChannels.splice(0, mutedChannels.length, ...parsedMutedChannels)
  }
} else {
  sessionStorage.setItem('mutedchannels', JSON.stringify(mutedChannels))
}

interface Admin {
  id: number;
}

interface Owner {
  id: number;
}

interface Message {
  text: string;
  sender: {
    id: number;
    login: string;
    nickname: string;
  };
  createdAt: Date;
}

interface SocketRes {
  channelId: number,
  message: {
    text: string;
    sender: {
      id: number;
      login: string;
      nickname: string;
    };
    createdAt: Date;
  }
}

export default defineComponent({
  name: 'ChatPage',
  components: {
    BlackSection,
    CustomButton,
    MessageBubble,
    ChatBox
  },
  data () {
    return {
      joinedChannels: [], // List of channels user has joined
      publicChannels: [], // List of public channels available to join
      currentChannel: {
        id: -1,
        password: '',
        administrators: [] as Admin[],
        owners: [] as Owner[],
        messages: [] as Message[]
      }, // Info related to the current channel
      userClicked: false,
      createChannelDialog: false,
      isBlocked: false,
      isBlocker: false,
      connection: new SocketioService(),
      activeUser: {
        id: -1,
        login: '',
        nickname: '',
        blocked: {
          data: [
            {
              blockedUsers: [
                {
                  id: -1
                }
              ]
            }
          ]
        }
      },
      otherUser: {
        id: -1,
        login: '',
        nickname: ''
      },
      newChannelData: {
        name: '',
        password: '',
        isPublic: true
      },
      chatMessage: {
        channelId: -1,
        userId: -1,
        text: ''
      },
      popupMessage: '',
      showPopup: false,
      fromUser: -1
    }
  },
  async mounted () {
    this.connection.setupSocketConnection('/chat')
    console.log('connection:', this.connection)
    this.connection.socket.on('userLeft', (data: any) => {
      console.log('User left from socket server Room #:', data)
    })
    this.connection.socket.on('userJoined', (data: any) => {
      console.log('userJoined from socket server Room #:', data)
    })
    this.connection.socket.on('receiveMessage', (data: SocketRes) => {
      console.log('received data from socket server:', data)
      if (this.currentChannel.id === data.channelId) {
        const receivedMessage = {
          text: data.message.text,
          sender: {
            id: data.message.sender.id,
            login: data.message.sender.login,
            nickname: data.message.sender.nickname
          },
          createdAt: data.message.createdAt
        }
        if (!this.activeUser.blocked.data[0].blockedUsers.some(blocked => blocked.id === data.message.sender.id) || data.message.sender.id === this.activeUser.id) {
          this.currentChannel.messages.push(receivedMessage)
        }
      }
    })
    this.connection.socket.on('receivePM', (data: any) => {
      const toast = useToast()

      this.fromUser = data.fromUser
      if (data.message.startsWith(apiKey) && this.activeUser.id === data.toUser) {
        const request = data.message.replace(apiKey, '')
        if (request === 'challenge') {
          this.popupMessage = 'You received a Challenge from: ' + data.fromUserName + '!'
          this.showPopup = true
        } else if (request === 'accept') {
          sessionStorage.setItem('challenge', 'accepted')
          window.location.href = '/gamecentre'
        } else if (request === 'ignore') {
          toast.info('Challenge ignored')
        } else if (request.startsWith('mute')) {
          const requestParts = request.split('|')
          const muteEndTime = parseInt(requestParts[1], 10)
          const channelId = parseInt(requestParts[2], 10)
          const currentTime = Math.floor(Date.now() / 1000)
          const secondsRemaining = muteEndTime - currentTime

          // Fins existing channel if there's already info for it, then add/update info
          const existingChannelIndex = mutedChannels.findIndex(item => item.channelId === channelId)
          if (existingChannelIndex !== -1) {
            mutedChannels[existingChannelIndex] = { channelId, muteEndTime }
          } else {
            mutedChannels.push({ channelId, muteEndTime })
          }

          sessionStorage.setItem('mutedchannels', JSON.stringify(mutedChannels))

          toast.info(`You have been muted for channel Id: ${channelId} for ${secondsRemaining} seconds`)
          console.log('mutedChannels:', mutedChannels)
        } else if (request.startsWith('unmute')) {
          const requestParts = request.split('|')
          const muteEndTime = -1
          const channelId = parseInt(requestParts[1], 10)

          // Fins existing channel if there's already info for it, then add/update info
          const existingChannelIndex = mutedChannels.findIndex(item => item.channelId === channelId)
          if (existingChannelIndex !== -1) {
            mutedChannels[existingChannelIndex] = { channelId, muteEndTime }
            sessionStorage.setItem('mutedchannels', JSON.stringify(mutedChannels))
          } else {
            return
          }

          toast.info(`You have been unmuted for channel Id: ${channelId}`)
          console.log('mutedChannels:', mutedChannels)
        }
      } else if (this.activeUser.id === data.toUser) {
        const message = 'You received a DM from: ' + data.fromUserName + '\nMessage: ' + data.message
        toast.info(message)
      }
    })
  },
  unmounted () {
    this.connection.socket.disconnect()
  },
  methods: {
    async switchChannel (channelId: number) {
      this.connection.socket.emit('leaveRoom', {
        id: this.currentChannel.id,
        userId: this.activeUser.id
      })
      const toast = useToast()
      try {
        const response = await API.get(`chat/channel/${channelId}`)

        if (response.data) {
          if (response.data.members.some((member: { id: number }) => member.id === this.activeUser.id)) {
            this.currentChannel = response.data
            this.currentChannel.messages = this.currentChannel.messages.filter(message => {
              // Remove all messages that are from blocked users
              return !this.activeUser.blocked.data[0].blockedUsers.some(user => user.id === message.sender.id)
            })
            console.log('channel data:', this.currentChannel)
            this.connection.socket.emit('joinRoom', this.currentChannel.id)
          } else if (response.data.isPublic === true) {
            const password = window.prompt('Channel password (blank for none):')
            try {
              const response = await API.put(`chat/${channelId}/add`, {
                user: this.activeUser.id,
                password: password
              })

              if (response.data) {
                this.currentChannel = response.data
                console.log('socket emit joinRoom')
                this.connection.socket.emit('joinRoom', this.currentChannel.id)
                this.connection.socket.emit('loadChannel', this.activeUser.id)
                location.reload()
              } else {
                toast.error('Cannot Join Channel')
              }
            } catch (error) {
              toast.error('Did Not Join Channel')
            }
          }
        } else {
          toast.error('Cannot Join Channel')
        }
      } catch (error) {
        toast.error('An error occurred while joining the channel')
        console.error('Error creating channel:', error)
      }
    },
    isMyMessage (message: any) {
      return message.sender.id === this.activeUser.id
    },
    async createChannel () {
      const toast = useToast()
      try {
        await API.get(`updateUserActivity/${this.activeUser.login}/1`)
        const response = await API.post('chat', {
          name: this.newChannelData.name,
          password: this.newChannelData.password,
          private: !this.newChannelData.isPublic,
          ownerId: this.activeUser.id
        })

        if (response.status === 201) {
          location.reload()
        } else {
          toast.error('Channel Creation Failed')
        }
      } catch (error) {
        toast.error('An error occurred while creating the channel')
        console.error('Error creating channel:', error)
      }
    },
    closeDialog () {
      this.createChannelDialog = false
    },
    openDialog () {
      this.createChannelDialog = true
    },
    isUserAdminOrOwner () {
      if (this.currentChannel.administrators && this.currentChannel.owners) {
        const isAdminOrOwner =
          this.currentChannel.administrators.some((admin: Admin) => admin.id === this.activeUser.id) ||
          this.currentChannel.owners.some((owner: Owner) => owner.id === this.activeUser.id)

        return isAdminOrOwner
      } else {
        return false
      }
    },
    async toggleUserActions (memberId: number) {
      const toast = useToast()
      try {
        await API.get(`updateUserActivity/${this.activeUser.login}/1`)
        const response = await API.get(`loginid?user=${memberId}`)

        if (response.data) {
          this.otherUser = response.data
          this.userClicked = true
          const blockCheck = await API.get(`block/are-blocked?idOne=${this.activeUser.id}&idTwo=${this.otherUser.id}`)
          if (blockCheck.data) {
            this.isBlocked = true
            if (blockCheck.data === this.activeUser.id) {
              this.isBlocker = true
            } else {
              this.isBlocker = false
            }
          } else {
            this.isBlocked = false
          }
        } else {
          toast.error('Cannot Get User Info')
        }
      } catch (error) {
        toast.error('An error occurred while getting user info')
        console.error('Error creating channel:', error)
      }
    },
    async blockUser () {
      const confirmation = window.confirm('Are you sure you want to block this user?')
      await API.get(`updateUserActivity/${this.activeUser.login}/1`)
      if (confirmation) {
        const toast = useToast()

        try {
          const response = await API.post('block/block', {
            userId: this.activeUser.id,
            blockId: this.otherUser.id
          })

          if (response.status === 201) {
            toast.success('User Blocked, refresh page if you still see their messages')
          } else {
            toast.error('User block failed')
          }
        } catch (error) {
          toast.error('User Block Failed')
        }
      }
    },
    async unblockUser () {
      const confirmation = window.confirm('Are you sure you want to unblock this user?')
      await API.get(`updateUserActivity/${this.activeUser.login}/1`)
      if (confirmation) {
        const toast = useToast()

        try {
          const response = await API.post('block/unblock', {
            userId: this.activeUser.id,
            blockId: this.otherUser.id
          })

          if (response.status === 201) {
            toast.success('User Unblocked')
          } else {
            toast.error('User unblock failed')
          }
        } catch (error) {
          toast.error('User Unblock Failed')
        }
      }
    },
    profileUser () {
      if (this.otherUser) {
        window.location.href = `http://${siteIP}/profile?user=${this.otherUser.login}`
      }
    },
    challenge () {
      const confirmation = window.confirm('Are you sure?')
      const toast = useToast()
      if (confirmation && this.otherUser.id !== this.activeUser.id) {
        this.connection.socket.emit('sendPM', {
          fromUser: this.activeUser.id,
          fromUserName: this.activeUser.nickname,
          toUser: this.otherUser.id,
          message: apiKey + 'challenge'
        })
        toast.info('Challenge Sent, waiting on user response')
      } else {
        toast.info('Challenge not sent')
      }
    },
    acceptChallenge () {
      const toast = useToast()
      this.connection.socket.emit('sendPM', {
        fromUser: this.activeUser.id,
        fromUserName: this.activeUser.nickname,
        toUser: this.fromUser,
        message: apiKey + 'accept'
      })
      this.showPopup = false
      sessionStorage.setItem('challenge', 'accepted')
      window.location.href = '/gamecentre'
    },
    ignoreChallenge () {
      const toast = useToast()
      this.connection.socket.emit('sendPM', {
        fromUser: this.activeUser.id,
        fromUserName: this.activeUser.nickname,
        toUser: this.fromUser,
        message: apiKey + 'ignore'
      })
      toast.info('Challenge ignored')
      this.showPopup = false
    },
    async sendPM () {
      const input = prompt('Enter a message:')
      const toast = useToast()
      if (!input) {
        toast.error('Message cannot be empty')
      } else {
        await API.get(`updateUserActivity/${activeUser}/1`)
        this.connection.socket.emit('sendPM', {
          fromUser: this.activeUser.id,
          fromUserName: this.activeUser.nickname,
          toUser: this.otherUser.id,
          message: input
        })
      }
    },
    async sendMessage (message: string) {
      const toast = useToast()
      const existingChannelIndex = mutedChannels.findIndex(item => item.channelId === this.currentChannel.id)
      const currentTimeInSeconds = Math.floor(Date.now() / 1000)

      if (typeof message === 'string') {
        if (this.currentChannel.id === -1) {
          toast.error('Join a channel first before messaging')
        } else if (existingChannelIndex !== -1) {
          const timeToWait = mutedChannels[existingChannelIndex].muteEndTime - currentTimeInSeconds

          if (timeToWait > 0) {
            toast.error(`You have been muted, and need to wait ${timeToWait} more seconds`)
          } else {
            await API.get(`updateUserActivity/${activeUser}/1`)
            this.chatMessage.channelId = this.currentChannel.id
            this.chatMessage.text = message
            this.connection.socket.emit('sendMessage', this.chatMessage)
          }
        } else {
          await API.get(`updateUserActivity/${activeUser}/1`)
          this.chatMessage.channelId = this.currentChannel.id
          this.chatMessage.text = message
          this.connection.socket.emit('sendMessage', this.chatMessage)
        }
      }
    },
    async addUser () {
      const toast = useToast()
      const userAdd = window.prompt('Enter their intra login to add user')
      if (userAdd) {
        const password = window.prompt('Enter the channel password')
        if (password) {
          try {
            const userres = await API.get(`login?user=${userAdd}`)
            if (userres.data) {
              const userId = userres.data.id
              const response = await API.put(`chat/${this.currentChannel.id}/add`, {
                user: userId,
                password: password
              })

              if (response.data) {
                this.currentChannel = response.data
                location.reload()
              } else {
                toast.error('Cannot Add User')
              }
            }
          } catch (error) {
            toast.error('Adding User Failed')
          }
        }
      }
    },
    muteUser () {
      const toast = useToast()
      if (this.otherUser.id === this.currentChannel.owners[0].id) {
        toast.error('You cannot mute owners')
      } else {
        const muteTime = window.prompt('Enter the number of seconds to mute (between 1 and 10000):')

        // User clicked cancel
        if (muteTime === null) {
          return
        }

        // User input validation check
        if (!/^\d+$/.test(muteTime)) {
          toast.error('Incorrect time entered. Please enter a valid number of seconds.')
          return
        }

        const muteTimeNumber = parseInt(muteTime, 10)
        const muteEndTime = Math.floor(Date.now() / 1000) + muteTimeNumber

        if (muteTimeNumber < 1 || muteTimeNumber > 10000) {
          toast.error('Mute time must be between 1 and 10000 seconds.')
          return
        }

        this.connection.socket.emit('sendPM', {
          fromUser: this.activeUser.id,
          fromUserName: this.activeUser.nickname,
          toUser: this.otherUser.id,
          message: apiKey + `mute|${muteEndTime}|${this.currentChannel.id}`
        })
        toast.info(`User Muted for ${muteTimeNumber} seconds`)
      }
    },
    unmuteUser () {
      const confirmation = window.confirm('Are you sure?')
      if (confirmation) {
        const toast = useToast()
        this.connection.socket.emit('sendPM', {
          fromUser: this.activeUser.id,
          fromUserName: this.activeUser.nickname,
          toUser: this.otherUser.id,
          message: apiKey + `unmute|${this.currentChannel.id}`
        })
        toast.info('User Unmuted')
      }
    },
    async kickUser () {
      const confirmation = window.confirm('Are you sure?')
      if (confirmation && activeUser) {
        const toast = useToast()
        try {
          const response = await API.delete(`chat/${this.currentChannel.id}/delete`, {
            data: {
              adminId: this.activeUser.id,
              deleteId: this.otherUser.id
            }
          })

          if (response.status === 200) {
            location.reload()
          } else {
            toast.error('Insufficient Privilege.')
          }
        } catch (error) {
          toast.error('Insufficient Privilege.')
        }
      }
    },
    async banUser () {
      const confirmation = window.confirm('Are you sure?')
      const toast = useToast()
      if (confirmation) {
        try {
          const response = await API.put(`chat/${this.currentChannel.id}/ban`, {
            adminId: this.activeUser.id,
            deleteId: this.otherUser.id
          })

          console.log('response:', response)

          if (response.data) {
            toast.success('User Banned')
          } else {
            toast.error('Ban User Failed')
          }
        } catch (error) {
          toast.error('Ban User Failed')
        }
      }
    },
    async unbanUser () {
      const userUnban = window.prompt('Enter their intra login to unmute:')
      const toast = useToast()
      if (userUnban) {
        try {
          const userres = await API.get(`login?user=${userUnban}`)
          if (userres.data) {
            const userId = userres.data.id
            const response = await API.put(`chat/${this.currentChannel.id}/unban`, {
              adminId: this.activeUser.id,
              deleteId: userId
            })

            if (response.data) {
              toast.success('User Unbanned')
            } else {
              toast.error('Unban User Failed')
            }
          } else {
            toast.error('User Not Found')
          }
        } catch (error) {
          toast.error('Unban User Failed')
        }
      }
    },
    async makeAdmin () {
      const toast = useToast()
      if (this.activeUser.id !== this.currentChannel.owners[0].id) {
        toast.error('You do not have enough privilege for that')
      } else {
        const confirmation = window.confirm('Are you sure? This action can only be reversed by kicking them.')
        if (confirmation) {
          try {
            const response = await API.put(`chat/${this.currentChannel.id}/makeadmin`, {
              adminId: this.activeUser.id,
              deleteId: this.otherUser.id
            })

            console.log('response:', response)

            if (response.data) {
              toast.success('User is now Admin')
            } else {
              toast.error('Make Admin Failed, Insufficient Privilege')
            }
          } catch (error) {
            toast.error('Make Admin Failed')
          }
        }
      }
    },
    async deleteChannel () {
      const toast = useToast()
      if (this.activeUser.id !== this.currentChannel.owners[0].id) {
        toast.error('You need to be the owner')
      } else {
        const confirmation = window.confirm('Are you REALLY sure? Tis be gone forever!')
        if (confirmation) {
          try {
            const response = await API.delete(`chat/${this.currentChannel.id}/deletechannel`)

            if (response.status === 200) {
              location.reload()
            } else {
              toast.error('Insufficient Privilege.')
            }
          } catch (error) {
            toast.error('Insufficient Privilege.')
          }
        }
      }
    },
    async parseUserinfo () {
      if (activeUser) {
        try {
          await API.get(`updateUserActivity/${activeUser}/1`)
          const response = await API.get(`login?user=${activeUser}`)
          this.activeUser.nickname = response.data.nickname
          this.activeUser.login = response.data.login
          this.activeUser.id = Number(response.data.id)
          this.activeUser.blocked = await API.get(`block/list?idOne=${response.data.id}`)
          this.chatMessage.userId = Number(response.data.id)
        } catch (error) {
          console.error('Internal Error:', error)
        }
        try {
          const response = await API.get(`chat/user/${this.activeUser.id}`)
          this.joinedChannels = response.data
        } catch (error) {
          console.error('Error creating channel:', error)
        }
        try {
          const response = await API.get('chat/public')
          this.publicChannels = response.data
        } catch (error) {
          console.error('Error creating channel:', error)
        }
      }
    }
  },
  created () {
    this.parseUserinfo()
  }
})
</script>

<style scoped>
.chat {
  display: flex;
  justify-content: center; /* Center align sections horizontally */
  align-items: flex-start; /* Align sections at the top vertically */
}

.channel-section {
  flex: 1; /* Take 1/3 of the available width */
  max-width: 200px; /* Set a maximum width for the channel section */
  margin-right: 20px; /* Add margin on the right to create space between sections */
}

.button-container {
  flex-grow: 1;
  display: flex;
  align-items: right;
}

.small-button {
  margin: 1px;
  width: 200px;
}

.big-button {
  margin: 1px;
  width: 350px;
}

.custom-button {
  margin-left: 10px;
}

.default-button {
  background-color: #71beba; /* Set the default background color */
  color: white; /* Set the text color */
}

.default-button:hover {
  background-color: #30807d; /* Set the background color on hover */
}

.block-button {
  background-color: red; /* Set the default background color */
  color: white; /* Set the text color */
}

.block-button:hover {
  background-color: darkred; /* Set the background color on hover */
}

.invite-button {
  background-color: green; /* Set the default background color */
  color: white; /* Set the text color */
}

.invite-button:hover {
  background-color: darkgreen; /* Set the background color on hover */
}

.spacing {
  margin-bottom: 0.5rem;
}

.general-chat-section {
  flex: 2; /* Take 2/3 of the available width */
  max-width: 400px; /* Set a maximum width for the general chat section */
  margin-right: 20px; /* Add margin on the right to create space between sections */
}

.players-section {
  flex: 1; /* Take 1/3 of the available width */
  max-width: 200px; /* Set a maximum width for the players section */
}

.title {
  margin: 0;
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-top: 2rem; /* Add top margin */
}

.title-line {
  width: 100%; /* Set the line to span the full width of the container */
  height: 1px; /* Set the height of the line */
  background: white; /* Set the background color to white */
  margin-top: 5px; /* Add some space between the line and the title */
  margin-bottom: 10px; /* Add some space between the line and the next element */
}

.black-section {
  width: 100%; /* Set full width for black sections on smaller screens */
  height: 530px; /* Set a specific height for the black sections */
  margin-bottom: 20px; /* Add margin-bottom to create space between rows */
  overflow: auto;
}

.app {
  height: 80%;
  display: flex;
  flex-direction: column;
  box-sizing: border-box; /* Include padding and border in the element's total height and width calculation */
}

.messages {
  height: 80%;
  flex: 1;
  overflow: auto;
  padding: 1rem;
  box-sizing: border-box; /* Include padding and border in the element's total height and width calculation */
}

.message + .message {
  margin-top: 1rem;
}

.message.right {
  margin-left: auto;
}

a {
  color: white;
}

</style>
