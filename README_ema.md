<h1><u>Minishell</u></h1>

<h2>Requirements:</h2>
<ol>
    <li>Handle environment variables ($ followed by a sequence of characters) which should expand to their values. <b>[100% Done]</b>
        <br /><img src="assets/img/env_expand.jpg" alt="Env expansion" />
        <br /><img src="assets/img/env_expand_no_key.jpg" alt="Env expansion for non-existent Key" />
        <br /><img src="assets/img/env_expand_invalid_key.jpg" alt="Env expansion for invalid key" />
    </li>
    <li>Handle $? which should expand to the exit status of the most recently executed foreground pipeline. <b>[100% Done]</b>
    <img src="assets/img/exit_expand.jpg" alt="Exit status expansion" />
</li>
    <li>Handle ctrl-C <b>[100% Done]</b>, ctrl-D <b>[100% Done]</b> and ctrl-\ <b>[100% Done]</b> which should behave like in bash.</li>
    <li>In interactive mode:
        <ul>
            <li>ctrl-C displays a new prompt on a new line. <b>[100% Done]</b><br />
                <img src="assets/img/ctrlC_prompt_nl.jpg" alt="ctrl-C displaying prompt on new line" />
            </li>
            <li>ctrl-D exits the shell. <b>[100% Done]</b><br />
                <img src="assets/img/ctrlC_prompt_nl.jpg" alt="ctrl-D exiting shell" />
            </li>
            <li>ctrl-\ does nothing. <b>[100% Done]</b></li>
        </ul>
    </li>
    <li>Must implement the following built-in commands:
        <ul>
            <li>echo with option -n <b>[100% Done]</b><br />
                <img src="assets/img/echo_nl.jpg" alt="echo default" /><br />
                <img src="assets/img/echo_no_nl.jpg" alt="echo no newline" />
            </li>
            <li>cd with only a relative or absolute path<br />
                <img src="assets/img/cd_home.jpg" alt="cd tilde (home)" /><br />
                <img src="assets/img/cd_home_invalid.jpg" alt="cd tilde (home) when invalid" /><br />
                <img src="assets/img/cd_oldpwd.jpg" alt="cd dash (oldpwd)" /><br />
                <img src="assets/img/cd_oldpwd_invalid.jpg" alt="cd dash (oldpwd) when invalid" /><br />
                <img src="assets/img/cd_permission.jpg" alt="cd into folder with no perms" />
            </li>
            <li>pwd with no options <b>[100% Done]</b><br />
                <img src="assets/img/pwd.jpg" alt="pwd default" /><br />
                <img src="assets/img/pwd_args.jpg" alt="pwd with args" />
            </li>
            <li>export with no options <b>[100% Done]</b><br />
                <img src="assets/img/export_declare.jpg" alt="export default" /><br />
                <img src="assets/img/export_invalid_identifier.jpg" alt="export invalid key" /><br />
                <img src="assets/img/export_malloc_error.jpg" alt="export malloc error" /><br />
                <img src="assets/img/export_no_val.jpg" alt="export no value" /><br />
                <img src="assets/img/export_no_val_res.jpg" alt="export no value result" /><br />
            </li>
            <li>unset with no options <b>[100% Done]</b><br />
                <img src="assets/img/unset.jpg" alt="unset no args" /><br />
                <img src="assets/img/unset_no_arg.jpg" alt="export default" />
            </li>
            <li>env with no options or arguments <b>[100% Done]</b><br />
                <img src="assets/img/env.jpg" alt="env default" /><br />
                <img src="assets/img/env_args.jpg" alt="env with args" />
            </li>
            <li>exit with no options <b>[100% Done]</b><br />
<img src="assets/img/exit.jpg" alt="exit" />
<img src="assets/img/exit_args.jpg" alt="exit with args" />
<img src="assets/img/exit_not_num.jpg" alt="exit not a number" />
<img src="assets/img/exit_big_num.jpg" alt="exit number bigger than long max" />
<img src="assets/img/exit_wrap.jpg" alt="exit number wrapping if >=256" />
<img src="assets/img/exit_wrap_res.jpg" alt="exit number wrapping if >=256 result" />
</li>
        </ul>
    </li>
</ol>