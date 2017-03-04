function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6370\" class=\"headerLeftMenuInActive\"><a id=\"aID6370\" href=\"#\" OnMouseOver=\"link('_dir','scissor0',this)\" class=\"leftMenuLinkHeadInActive\">scissor</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID875\" class=\"leftMenuInActive\"><a id=\"aID875\" href=\"#\" OnMouseOver=\"link('_class','FrameScissor54809',this)\" class=\"leftMenuLinkInActive\">FrameScissor</a></div>\n");
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
