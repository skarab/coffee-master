function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6362\" class=\"headerLeftMenuInActive\"><a id=\"aID6362\" href=\"#\" OnMouseOver=\"link('_dir','gbuffer0',this)\" class=\"leftMenuLinkHeadInActive\">gbuffer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID865\" class=\"leftMenuInActive\"><a id=\"aID865\" href=\"#\" OnMouseOver=\"link('_class','FramePassGBuffer54809',this)\" class=\"leftMenuLinkInActive\">FramePassGBuffer</a></div>\n");
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
