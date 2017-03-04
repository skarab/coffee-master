function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6355\" class=\"headerLeftMenuInActive\"><a id=\"aID6355\" href=\"#\" OnMouseOver=\"link('_dir','device0',this)\" class=\"leftMenuLinkHeadInActive\">device</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6354\" class=\"leftMenuInActive\"><a id=\"aID6354\" href=\"#\" OnMouseOver=\"link('_dir','config/config0',this)\" class=\"leftMenuLinkInActive\">config</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID857\" class=\"leftMenuInActive\"><a id=\"aID857\" href=\"#\" OnMouseOver=\"link('_class','Device54809',this)\" class=\"leftMenuLinkInActive\">Device</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6229\" class=\"leftMenuInActive\"><a id=\"aID6229\" href=\"#\" OnMouseOver=\"link('_member','DEVICE_SUPPORT827376375',this)\" class=\"leftMenuLinkInActive\">DEVICE_SUPPORT</a></div>\n");
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
