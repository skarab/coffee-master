function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6329\" class=\"headerLeftMenuInActive\"><a id=\"aID6329\" href=\"#\" OnMouseOver=\"link('_dir','state0',this)\" class=\"leftMenuLinkHeadInActive\">state</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID818\" class=\"leftMenuInActive\"><a id=\"aID818\" href=\"#\" OnMouseOver=\"link('_class','State41582',this)\" class=\"leftMenuLinkInActive\">State</a></div>\n");
document.write("<div id=\"divID819\" class=\"leftMenuInActive\"><a id=\"aID819\" href=\"#\" OnMouseOver=\"link('_class','StateMachine41582',this)\" class=\"leftMenuLinkInActive\">StateMachine</a></div>\n");
document.write("<div id=\"divID820\" class=\"leftMenuInActive\"><a id=\"aID820\" href=\"#\" OnMouseOver=\"link('_class','StateTransition41582',this)\" class=\"leftMenuLinkInActive\">StateTransition</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
